#include "XMLFileReader.h"

#include <spdlog/fmt/bundled/core.h>

#include <filesystem>
#include <optional>
#include <regex>
#include <sstream>

#include "io/input/chkpt/ChkptPointFileReader.h"
#include "io/logger/Logger.h"
#include "io/xml_schemas/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "simulation/Simulation.h"

std::string convertToPath(const std::string& base_path, const std::string& path) {
    if (path.empty()) {
        return "";
    }

    auto is_relative_path = path[0] != '/';

    if (is_relative_path) {
        return std::filesystem::path(base_path).parent_path().string() + "/" + path;
    } else {
        return path;
    }
}

std::tuple<std::vector<Particle>, SimulationParams> construct_configuration(std::string curr_file_path, ConfigurationType& config,
                                                                            bool fresh, int depth = 0, std::string base_path = "") {
    Logger::logger->info("Constructing configuration for file {} at depth {}", curr_file_path, depth);

    auto settings = config.settings();
    auto particle_sources = config.particle_source();

    std::vector<Particle> particles;

    auto container_type = XSDToInternalTypeAdapter::convertToParticleContainer(settings.particle_container());

    auto forces = XSDToInternalTypeAdapter::convertToForces(settings.force());

    auto params = SimulationParams{curr_file_path,
                                   "",
                                   settings.delta_t(),
                                   settings.end_time(),
                                   static_cast<int>(settings.fps()),
                                   static_cast<int>(settings.video_length()),
                                   container_type,
                                   "vtu",
                                   forces,
                                   false,
                                   fresh,
                                   base_path};

    // Spawn particles specified in the XML file
    for (auto cuboid_spawner : particle_sources.cuboid_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToCuboidSpawner(cuboid_spawner, settings.third_dimension());
        int num_spawned = spawner.spawnParticles(particles);
        Logger::logger->info("Spawned {} particles from cuboid spawner", num_spawned);
    }

    for (auto sphere_spawner : particle_sources.sphere_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToSphereSpawner(sphere_spawner, settings.third_dimension());
        int num_spawned = spawner.spawnParticles(particles);
        Logger::logger->info("Spawned {} particles from sphere spawner", num_spawned);
    }

    for (auto single_particle_spawner : particle_sources.single_particle_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToSingleParticleSpawner(single_particle_spawner, settings.third_dimension());
        int num_spawned = spawner.spawnParticles(particles);
        Logger::logger->info("Spawned {} particles from single particle spawner", num_spawned);
    }

    for (auto checkPointLoader : particle_sources.check_point_loader()) {
        auto path = convertToPath(curr_file_path, checkPointLoader.file_name());

        std::string file_extension = path.substr(path.find_last_of('.'));
        if (file_extension != ".chkpt") {
            Logger::logger->error("Error: file extension '{}' is not supported. Only .chkpt files can be used as checkpoints.",
                                  file_extension);
            exit(-1);
        }

        ChkptPointFileReader reader;
        auto [loaded_particles, _] = reader.readFile(path);

        particles.insert(particles.end(), loaded_particles.begin(), loaded_particles.end());

        Logger::logger->info("Loaded {} particles from checkpoint file {}", loaded_particles.size(), path);
    }

    int sub_simulation_counter = 0;

    for (auto sub_simulation : particle_sources.sub_simulation()) {
        depth++;
        Logger::logger->info("Found sub simulation source {} at depth {}", sub_simulation_counter, depth);

        std::string cache_dir_path = params.output_dir_path + "sub/" + std::to_string(sub_simulation_counter) + "/";
        std::optional<std::string> cached_file_path = std::nullopt;

        // Try to find a checkpoint file in the cache directory
        if (std::filesystem::exists(cache_dir_path) && !fresh) {
            auto last_checkpoint = -1;
            for (const auto& entry : std::filesystem::directory_iterator(cache_dir_path)) {
                if (entry.path().extension() == ".chkpt") {
                    std::string current_file_path = entry.path().string();
                    auto current_file_number =
                        std::stoi(std::regex_replace(current_file_path, std::regex("[^0-9]*([0-9]+).*"), std::string("$1")));

                    if (cached_file_path.has_value()) {
                        if (current_file_number > last_checkpoint) {
                            cached_file_path = current_file_path;
                            last_checkpoint = current_file_number;
                        }
                    } else {
                        cached_file_path = current_file_path;
                        last_checkpoint = current_file_number;
                    }
                }
            }
        }

        // If a checkpoint file was found, load it. Otherwise, run a sub simulation
        if (cached_file_path.has_value()) {
            Logger::logger->warn(
                "Using cached result for sub simulation {} at depth {}. To force a rerun, delete the checkpoint file at {}",
                sub_simulation_counter, depth, *cached_file_path);

            ChkptPointFileReader reader;
            auto [loaded_particles, _] = reader.readFile(*cached_file_path);

            particles.insert(particles.end(), loaded_particles.begin(), loaded_particles.end());

            Logger::logger->warn("Loaded {} particles from checkpoint file {}", loaded_particles.size(), *cached_file_path);
        } else {
            Logger::logger->info("Starting sub simulation {} at depth {}", sub_simulation_counter, depth);

            auto [loaded_config, file_name] = [curr_file_path, sub_simulation, params, depth, sub_simulation_counter]() {
                if (sub_simulation.configuration()) {
                    return std::make_tuple(*sub_simulation.configuration(), params.input_file_path + " sub{depth:" + std::to_string(depth) +
                                                                                ", num:" + std::to_string(sub_simulation_counter) + "}");
                } else if (sub_simulation.file_name()) {
                    auto path = convertToPath(curr_file_path, sub_simulation.file_name().get());

                    std::string file_extension = path.substr(path.find_last_of('.'));
                    if (file_extension != ".xml") {
                        Logger::logger->error(
                            "Error: file extension '{}' is not supported. Only .xml files can be used as sub simulations.", file_extension);
                        exit(-1);
                    }

                    return std::make_tuple(*configuration(path), path);
                } else {
                    Logger::logger->error("Error: sub simulation source must contain either a configuration or a file name.");
                    exit(-1);
                }
            }();

            auto [sub_particles, sub_config] = construct_configuration(file_name, loaded_config, fresh, depth, cache_dir_path);

            sub_config.output_dir_path = cache_dir_path;
            sub_config.output_format = OutputFormat::VTU;

            Simulation simulation{sub_particles, sub_config};

            sub_config.logSummary(depth);

            auto result = simulation.runSimulation();

            result.logSummary(depth);

            particles.insert(particles.end(), result.resulting_particles.begin(), result.resulting_particles.end());

            Logger::logger->info("Finished configuration {} for file {} at depth {}", sub_simulation_counter, file_name, depth);
            Logger::logger->info("Wrote {} particles to checkpoint file in: {}", result.resulting_particles.size(),
                                 result.simulation_params.output_dir_path);
        }

        sub_simulation_counter++;
    }

    params.num_particles = particles.size();

    return std::make_tuple(particles, std::move(params));
}

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> XMLFileReader::readFile(const std::string& filepath) const {
    try {
        auto config = configuration(filepath);

        return construct_configuration(filepath, *config, fresh);
    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
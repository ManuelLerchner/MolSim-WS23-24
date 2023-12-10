#include "XMLFileReader.h"

#include <spdlog/fmt/bundled/core.h>

#include <filesystem>
#include <optional>
#include <sstream>

#include "io/input/chkpt/ChkptPointFileReader.h"
#include "io/logger/Logger.h"
#include "io/output/FileOutputHandler.h"
#include "io/xml_schemas/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "simulation/Simulation.h"

std::string trim(const std::string& str) {
    // skip whitespace and newlines
    auto start = str.find_first_not_of(" \t\n\r\f\v");
    auto end = str.find_last_not_of(" \t\n\r\f\v");

    if (start == std::string::npos) {
        return "";
    } else {
        return str.substr(start, end - start + 1);
    }
}

std::string sanitizePath(const std::string& text) {
    std::string sanitized = text;

    // Replace all backslashes with forward slashes
    std::replace(sanitized.begin(), sanitized.end(), '\\', '/');

    // Remove trailing slashes
    if (sanitized.back() == '/') {
        sanitized.pop_back();
    }

    // replace spaces with underscores
    std::replace(sanitized.begin(), sanitized.end(), ' ', '_');

    // to lower case
    std::transform(sanitized.begin(), sanitized.end(), sanitized.begin(), [](unsigned char c) { return std::tolower(c); });

    return sanitized;
}

std::string convertToPath(const std::string& base_path, const std::string& path) {
    if (path.empty()) {
        return "";
    }

    auto is_relative_path = path[0] != '/';

    if (is_relative_path) {
        return base_path + "/" + path;
    } else {
        return path;
    }
}

void loadCheckpointFile(std::vector<Particle>& particles, const std::string& path) {
    std::string file_extension = path.substr(path.find_last_of('.'));
    if (file_extension != ".chkpt") {
        Logger::logger->error("Error: file extension '{}' is not supported. Only .chkpt files can be used as checkpoints.", file_extension);
        exit(-1);
    }

    ChkptPointFileReader reader;
    auto [loaded_particles, _] = reader.readFile(path);
    particles.insert(particles.end(), loaded_particles.begin(), loaded_particles.end());

    Logger::logger->info("Loaded {} particles from checkpoint file {}", loaded_particles.size(), path);
}

std::optional<std::string> getCheckPointFilePath(const std::string& base_path) {
    if (!std::filesystem::exists(base_path)) {
        return std::nullopt;
    }

    std::optional<std::string> checkPointPath = std::nullopt;
    auto best_iteration = -1;
    for (const auto& entry : std::filesystem::directory_iterator(base_path)) {
        if (entry.path().extension() == ".chkpt") {
            std::string current_file_path = entry.path().string();

            auto num_start = current_file_path.find_first_of("0123456789");
            auto num_end = current_file_path.find_last_of("0123456789");

            auto current_file_number = std::stoi(current_file_path.substr(num_start, num_end - num_start + 1));

            if (current_file_number > best_iteration) {
                best_iteration = current_file_number;
                checkPointPath = current_file_path;
            }
        }
    }

    return checkPointPath;
}

auto load_config(const SubSimulationType& sub_simulation, const std::string& curr_file_path, const std::string& base_path) {
    if (sub_simulation.configuration()) {
        // Configuration is diretly in the XML file
        auto loaded_config = *sub_simulation.configuration();

        return std::make_pair(loaded_config, curr_file_path + " |> Sub: " + sub_simulation.name());
    } else if (sub_simulation.file_name()) {
        // Configuration is in a separate file
        auto other_file_name = convertToPath(base_path, sub_simulation.file_name().get());

        std::string file_extension = other_file_name.substr(other_file_name.find_last_of('.'));
        if (file_extension != ".xml") {
            Logger::logger->error("Error: file extension '{}' is not supported. Only .xml files can be used as sub simulations.",
                                  file_extension);
            exit(-1);
        }

        return std::make_pair(*configuration(other_file_name), other_file_name);
    } else {
        Logger::logger->error("Error: sub simulation source must contain either a configuration or a file name.");
        exit(-1);
    }
}

auto checkCheckPointHashIsValid(const std::string& path) {
    auto checkpoint = CheckPoint(path, xml_schema::flags::dont_validate);
    auto metaData = checkpoint->MetaData();

    std::ifstream input_file(metaData.input_file());

    auto buffer = std::stringstream();
    buffer << input_file.rdbuf();

    std::hash<std::string> hasher;
    auto curr_hash = hasher(buffer.str());

    return curr_hash == metaData.input_file_hash();
}

std::tuple<std::vector<Particle>, SimulationParams> prepare_particles(std::string curr_file_path, ConfigurationType& config, bool fresh,
                                                                      bool allow_recursion, std::string output_base_path = "",
                                                                      int depth = 0) {
    Logger::logger->info("Constructing configuration for file {} at depth {}", curr_file_path, depth);

    auto settings = config.settings();
    auto particle_sources = config.particle_source();

    std::vector<Particle> particles;

    auto container_type = XSDToInternalTypeAdapter::convertToParticleContainer(settings.particle_container());

    auto xsd_thermostat = settings.thermostat();
    auto thermostat = (xsd_thermostat)
                          ? std::make_optional(XSDToInternalTypeAdapter::convertToThermostat(*xsd_thermostat, settings.third_dimension()))
                          : std::nullopt;

    auto forces = XSDToInternalTypeAdapter::convertToForces(settings.forces());

    auto params = SimulationParams{curr_file_path,
                                   "",
                                   settings.delta_t(),
                                   settings.end_time(),
                                   static_cast<int>(settings.fps()),
                                   static_cast<int>(settings.video_length()),
                                   container_type,
                                   thermostat,
                                   "vtu",
                                   std::move(forces),
                                   false,
                                   fresh,
                                   output_base_path};

    if (output_base_path.empty()) {
        output_base_path = params.output_dir_path;
    }

    auto curr_folder = std::filesystem::path(curr_file_path).parent_path().string();

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
        auto path = convertToPath(curr_folder, checkPointLoader.file_name());
        loadCheckpointFile(particles, path);
    }

    for (auto sub_simulation : particle_sources.sub_simulation()) {
        if (!allow_recursion) {
            Logger::logger->warn("Error: Recursion is disabled. Skipping sub simulation at depth {}", depth);
            continue;
        }

        auto name = trim(sub_simulation.name());

        depth++;
        Logger::logger->info("Found sub simulation {} at depth {}", name, depth);

        std::string new_output_base_path = output_base_path + "/" + sanitizePath(name);

        // Try to find a checkpoint file in the base directory
        auto checkpoint_path = fresh ? std::nullopt : getCheckPointFilePath(new_output_base_path);

        // If no checkpoint file was found, run the sub simulation
        if (checkpoint_path.has_value()) {
            Logger::logger->info("Found checkpoint file for sub simulation {} at depth {}", name, depth);

            // checking if the hash of the input file is the same as the one in the checkpoint file
            auto hash_valid = checkCheckPointHashIsValid(*checkpoint_path);

            if (!hash_valid) {
                Logger::logger->warn(
                    "The input file for sub simulation {} at depth {} has changed since the checkpoint file was created. The simulation is "
                    "going to be repeated.",
                    name, depth);
                checkpoint_path = std::nullopt;
            } else {
                Logger::logger->warn(
                    "Using cached result for sub simulation {} at depth {}. To force a rerun, delete the checkpoint file at {}", name,
                    depth, *checkpoint_path);
            }
        }

        if (!checkpoint_path.has_value()) {
            Logger::logger->info("Starting sub simulation {} at depth {}", name, depth);

            // Load the configuration from the sub simulation
            auto [loaded_config, file_name] = load_config(sub_simulation, curr_file_path, curr_folder);

            // Create the initial conditions for the sub simulation
            auto [sub_particles, sub_config] =
                prepare_particles(file_name, loaded_config, fresh, allow_recursion, new_output_base_path, depth);
            sub_config.output_dir_path = new_output_base_path;
            sub_config.output_format = OutputFormat::NONE;

            // Run the sub simulation
            Simulation simulation{sub_particles, sub_config};

            sub_config.logSummary(depth);
            auto result = simulation.runSimulation();
            result.logSummary(depth);

            // Write the checkpoint file
            auto checkpoint_config = sub_config;
            checkpoint_config.output_format = OutputFormat::CHKPT;

            FileOutputHandler file_output_handler{checkpoint_config};

            checkpoint_path = file_output_handler.writeFile(result.total_iterations, result.resulting_particles);

            Logger::logger->info("Wrote {} particles to checkpoint file in: {}", result.resulting_particles.size(),
                                 result.params.output_dir_path);
        }

        // Load the checkpoint file
        loadCheckpointFile(particles, *checkpoint_path);
    }

    params.num_particles = particles.size();

    return std::make_tuple(particles, std::move(params));
}

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> XMLFileReader::readFile(const std::string& filepath) const {
    try {
        auto config = configuration(filepath);

        return prepare_particles(filepath, *config, fresh, allow_recursion);
    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
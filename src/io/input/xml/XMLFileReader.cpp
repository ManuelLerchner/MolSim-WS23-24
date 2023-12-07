#include "XMLFileReader.h"

#include <spdlog/fmt/bundled/core.h>

#include <filesystem>
#include <optional>
#include <sstream>

#include "io/input/chkpt/ChkptPointFileReader.h"
#include "io/logger/Logger.h"
#include "io/xml_schemas/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "simulation/Simulation.h"

std::tuple<std::vector<Particle>, SimulationParams> construct_configuration(std::string curr_file_path, ConfigurationType& config) {
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
                                   "vtk",
                                   forces,
                                   false};

    int sub_simulation_counter = 0;

    // Spawn particles specified in the XML file
    for (auto cuboid_spawner : particle_sources.cuboid_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToCuboidSpawner(cuboid_spawner, settings.third_dimension());
        spawner.spawnParticles(particles);
    }

    for (auto sphere_spawner : particle_sources.sphere_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToSphereSpawner(sphere_spawner, settings.third_dimension());
        spawner.spawnParticles(particles);
    }

    for (auto single_particle_spawner : particle_sources.single_particle_spawner()) {
        auto spawner = XSDToInternalTypeAdapter::convertToSingleParticleSpawner(single_particle_spawner, settings.third_dimension());
        spawner.spawnParticles(particles);
    }

    for (auto checkPointLoader : particle_sources.check_point_loader()) {
        auto path = checkPointLoader.file_name();

        auto is_relative_path = path[0] != '/';

        if (is_relative_path) {
            path = std::filesystem::path(curr_file_path).parent_path().string() + "/" + path;
        }

        std::string file_extension = path.substr(path.find_last_of('.'));

        if (file_extension != ".chkpt") {
            Logger::logger->error("Error: file extension '{}' is not supported.", file_extension);
            exit(-1);
        }

        ChkptPointFileReader reader;
        auto [loaded_particles, _] = reader.readFile(path);

        particles.insert(particles.end(), loaded_particles.begin(), loaded_particles.end());
    }

    for (auto sub_simulation : particle_sources.sub_simulation()) {
        std::string sub_file_path = params.output_dir_path + "sub/" + std::to_string(sub_simulation_counter++);

        auto [sub_particles, sub_config] = construct_configuration(sub_file_path, sub_simulation);

        sub_config.fps = 0;
        sub_config.video_length = 0;
        sub_config.output_format = FileOutputHandler::OutputFormat::CHKPT;

        Simulation simulation{sub_particles, sub_config};

        auto result = simulation.runSimulation();

        particles.insert(particles.end(), result.resulting_particles.begin(), result.resulting_particles.end());
    }

    return std::make_tuple(particles, std::move(params));
}

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> XMLFileReader::readFile(const std::string& filepath) const {
    try {
        auto config = configuration(filepath);

        return construct_configuration(filepath, *config);

    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
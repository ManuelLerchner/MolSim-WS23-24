#include "XMLFileReader.h"

#include <optional>
#include <sstream>

#include "io/input/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> XMLFileReader::readFile(const std::string& filepath) const {
    try {
        auto config = configuration_(filepath);

        auto settings = config->settings();
        auto particle_spawners = config->particles();

        std::vector<Particle> particles;

        // Spawn particles specified in the XML file
        for (auto xsd_cuboid : particle_spawners.cuboid_spawner()) {
            auto spawner = XSDToInternalTypeAdapter::convertToCuboidSpawner(xsd_cuboid, settings.third_dimension());
            spawner.spawnParticles(particles);
        }

        for (auto xsd_sphere : particle_spawners.sphere_spawner()) {
            auto spawner = XSDToInternalTypeAdapter::convertToSphereSpawner(xsd_sphere, settings.third_dimension());
            spawner.spawnParticles(particles);
        }

        for (auto xsd_single_particle_spawner : particle_spawners.single_particle_spawner()) {
            auto spawner =
                XSDToInternalTypeAdapter::convertToSingleParticleSpawner(xsd_single_particle_spawner, settings.third_dimension());
            spawner.spawnParticles(particles);
        }

        // Create particle container
        auto container_type = XSDToInternalTypeAdapter::convertToParticleContainer(settings.particle_container());

        return std::make_tuple(particles, std::make_optional(SimulationParams{
                                              filepath, "", settings.delta_t(), settings.end_time(), static_cast<int>(settings.fps()),
                                              static_cast<int>(settings.video_length()), container_type, "vtk"}));
    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
#include "ChkptPointFileReader.h"

#include <sstream>

#include "io/input/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"

SimulationParams ChkptPointFileReader::readFile(const std::string& filepath, std::unique_ptr<ParticleContainer>& particle_container) const {
    try {
        auto checkpoint = CheckPoint(filepath, xml_schema::flags::dont_validate);

        auto particleData = checkpoint->ParticleData();

        std::vector<Particle> particles;

        for (auto xsd_particle : particleData.particle()) {
            auto particle = XSDToInternalTypeAdapter::convertToParticle(xsd_particle);
            particles.push_back(particle);
        }

        // Create particle container
        particle_container = std::make_unique<DirectSumContainer>();

        particle_container->reserve(particle_container->size() + particles.size());

        for (auto& particle : particles) {
            particle_container->addParticle(particle);
        }

        return SimulationParams{filepath, "", 0.0002, 5, 24, 30, SimulationParams::DirectSumType(), "vtk"};

    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
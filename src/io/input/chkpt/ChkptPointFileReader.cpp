#include "ChkptPointFileReader.h"

#include <sstream>

#include "io/input/xsd_type_adaptors/XSDToInternalTypeAdapter.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> ChkptPointFileReader::readFile(const std::string& filepath) const {
    try {
        auto checkpoint = CheckPoint(filepath, xml_schema::flags::dont_validate);

        auto particleData = checkpoint->ParticleData();

        std::vector<Particle> particles;

        for (auto xsd_particle : particleData.particle()) {
            auto particle = XSDToInternalTypeAdapter::convertToParticle(xsd_particle);
            particles.push_back(std::move(particle));
        }

        return std::make_tuple(particles, std::nullopt);
    } catch (const xml_schema::exception& e) {
        std::stringstream error_message;
        error_message << "Error: could not parse file '" << filepath << "'.\n";
        error_message << e << std::endl;
        throw FileFormatException(error_message.str());
    }
}
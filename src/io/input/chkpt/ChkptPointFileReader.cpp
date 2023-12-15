#include "ChkptPointFileReader.h"

#include <sstream>

#include "io/logger/Logger.h"
#include "io/xml_schemas/xsd_type_adaptors/XSDToInternalTypeAdapter.h"

void summarizeMetadata(MetaDataDataType m) {
    Logger::logger->info("Loaded checkpoint file with following metadata:");
    Logger::logger->info("  - Original file: {}", m.input_file());
    Logger::logger->info("  - Original file hash: {}", m.input_file_hash());
    Logger::logger->info("  - Original End time: {}", m.end_time());
    Logger::logger->info("  - Original Delta t: {}", m.delta_t());
}

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> ChkptPointFileReader::readFile(
    const std::filesystem::path& filepath) const {
    try {
        auto checkpoint = CheckPoint(filepath, xml_schema::flags::dont_validate);

        auto particle_data = checkpoint->ParticleData();
        auto meta_data = checkpoint->MetaData();

        summarizeMetadata(meta_data);

        std::vector<Particle> particles;

        for (auto xsd_particle : particle_data.particle()) {
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
#include "CheckPointWriter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "io/xml_schemas/xsd_type_adaptors/InternalToXSDTypeAdapter.h"

void CheckPointWriter::writeFile(const SimulationParams& params, int iteration,
                                 const std::unique_ptr<ParticleContainer>& particle_container) const {
    auto filename = params.output_dir_path + "/" + "MD_CHKPT";

    std::stringstream strstr;
    strstr << filename << "_" << std::setfill('0') << std::setw(4) << iteration << ".chkpt";

    MetaDataDataType meta_data{params.input_file_path, params.input_file_hash, params.end_time, params.delta_t};

    CheckPointFileType::ParticleData_type particles{};

    particles.particle().reserve(particle_container->size());

    for (const Particle& particle : *particle_container) {
        particles.particle().push_back(InternalToXSDTypeAdapter::convertToParticle(particle));
    }

    CheckPointFileType checkpointfile(meta_data, particles);

    std::ofstream file(strstr.str().c_str());
    CheckPoint(file, checkpointfile);
    file.close();
}
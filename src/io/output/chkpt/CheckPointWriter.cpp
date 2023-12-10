#include "CheckPointWriter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "io/xml_schemas/xsd_type_adaptors/InternalToXSDTypeAdapter.h"

const std::string CheckPointWriter::writeFile(const SimulationParams& params, size_t iteration,
                                              const std::vector<Particle>& particles) const {
    auto file_base = params.output_dir_path + "/" + "MD_CHKPT";

    std::stringstream strstr;
    strstr << file_base << "_" << std::setfill('0') << std::setw(4) << iteration << ".chkpt";

    MetaDataDataType meta_data{params.input_file_path, params.input_file_hash, params.end_time, params.delta_t};

    CheckPointFileType::ParticleData_type xsd_particles{};

    xsd_particles.particle().reserve(particles.size());

    for (const Particle& particle : particles) {
        xsd_particles.particle().push_back(InternalToXSDTypeAdapter::convertToParticle(particle));
    }

    CheckPointFileType checkpointfile(meta_data, xsd_particles);

    auto file_name = strstr.str();

    std::ofstream file(file_name.c_str());
    CheckPoint(file, checkpointfile);
    file.close();

    return file_name;
}
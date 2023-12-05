

#include "CheckPointWriter.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "io/logger/Logger.h"

void CheckPointWriter::writeFile(const std::string& output_dir_path, int iteration,
                                 const std::unique_ptr<ParticleContainer>& particle_container) const {
    auto filename = output_dir_path + "/" + "MD_CHKPT.ckpt";

    std::stringstream strstr;
    strstr << filename << std::setfill('0') << std::setw(6) << iteration;

    CheckPointFileType::ParticleData_type particles{};

    particles.particle().reserve(particle_container->size());

    for (const Particle& particle : *particle_container) {
        particles.particle().push_back(InternalToXSDTypeAdapter::convertToParticle(particle));
    }

    CheckPointFileType checkpointfile(particles);

    std::ofstream file(strstr.str().c_str());
    CheckPoint(file, checkpointfile);
    file.close();
}
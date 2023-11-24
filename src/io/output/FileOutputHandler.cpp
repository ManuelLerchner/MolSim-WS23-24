#include "FileOutputHandler.h"

#include <filesystem>
#include <iostream>

#include "io/logger/Logger.h"

FileOutputHandler::FileOutputHandler(const OutputFormat output_format, const std::string& output_dir_path)
    : output_format(output_format), output_dir_path(output_dir_path) {
    if (output_format == OutputFormat::NONE) {
        return;
    }

    if (std::filesystem::exists(output_dir_path)) {
        std::filesystem::remove_all(output_dir_path);
    }
    std::filesystem::create_directories(output_dir_path);
}

void FileOutputHandler::writeFile(int iteration, const std::unique_ptr<ParticleContainer>& particle_container) const {
    switch (output_format) {
        case OutputFormat::VTK:
            writeVTKFile(output_dir_path, iteration, particle_container);
            break;
        case OutputFormat::XYZ:
            writeXYZFile(output_dir_path, iteration, particle_container);
            break;
        case OutputFormat::NONE:
            break;
        default:
            Logger::logger->error("Output format not implemented.");
            exit(1);
    }
}

void FileOutputHandler::writeVTKFile(const std::string& output_dir_path, int iteration,
                                     const std::unique_ptr<ParticleContainer>& particle_container) const {
    VTKWriter vtk_writer;

    vtk_writer.initializeOutput(particle_container->size());

    for (const Particle& particle : *particle_container) {
        vtk_writer.plotParticle(particle);
    }

    vtk_writer.writeFile(output_dir_path + "/" + "MD_VTK", iteration);
}

void FileOutputHandler::writeXYZFile(const std::string& output_dir_path, int iteration,
                                     const std::unique_ptr<ParticleContainer>& particle_container) const {
    XYZWriter xyz_writer;

    xyz_writer.plotParticles(particle_container, output_dir_path + "/" + "MD_XYZ", iteration);
}

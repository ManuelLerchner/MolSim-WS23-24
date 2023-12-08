#include "FileOutputHandler.h"

#include <filesystem>

#include "io/logger/Logger.h"

FileOutputHandler::FileOutputHandler(const OutputFormat output_format, const std::string& output_dir_path)
    : output_format(output_format), output_dir_path(output_dir_path) {
    switch (output_format) {
        case OutputFormat::NONE:
            return;
        case OutputFormat::VTU:
            file_writer = std::make_unique<VTUWriter>();
            break;
        case OutputFormat::XYZ:
            file_writer = std::make_unique<XYZWriter>();
            break;
        case OutputFormat::CHKPT:
            file_writer = std::make_unique<CheckPointWriter>();
            break;
        default:
            Logger::logger->error("Output format not implemented.");
            exit(1);
    }

    if (std::filesystem::exists(output_dir_path)) {
        Logger::logger->warn("Output directory '{}' already exists.", output_dir_path);

        auto supported = FileOutputHandler::get_supported_output_formats();
        auto file_extension = std::find_if(supported.begin(), supported.end(), [output_format](const auto& pair) {
                                  return pair.second == output_format;
                              })->first;

        Logger::logger->warn("Deleting all files in directory with file extension '{}'", file_extension);

        auto count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(output_dir_path)) {
            if (entry.path().extension() == "." + file_extension) {
                std::filesystem::remove(entry.path());
                count++;
            }
        }

        Logger::logger->warn("Deleted {} files.", count);
    } else {
        Logger::logger->info("Creating output directory '{}'.", output_dir_path);
        std::filesystem::create_directories(output_dir_path);
    }
}

void FileOutputHandler::writeFile(int iteration, const std::unique_ptr<ParticleContainer>& particle_container) const {
    if (output_format == OutputFormat::NONE) {
        return;
    }
    file_writer->writeFile(output_dir_path, iteration, particle_container);
}

std::map<std::string, FileOutputHandler::OutputFormat> FileOutputHandler::get_supported_output_formats() {
    return {{"vtu", FileOutputHandler::OutputFormat::VTU},
            {"xyz", FileOutputHandler::OutputFormat::XYZ},
            {"chkpt", FileOutputHandler::OutputFormat::CHKPT},
            {"none", FileOutputHandler::OutputFormat::NONE}};
}
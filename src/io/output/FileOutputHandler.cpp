#include "FileOutputHandler.h"

#include <filesystem>

#include "io/logger/Logger.h"

FileOutputHandler::FileOutputHandler(const SimulationParams& params) : params(params) {
    switch (params.output_format) {
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

    if (std::filesystem::exists(params.output_dir_path)) {
        Logger::logger->warn("Output directory '{}' already exists.", params.output_dir_path);

        auto supported = get_supported_output_formats();
        auto file_extension = std::find_if(supported.begin(), supported.end(), [params](const auto& pair) {
                                  return pair.second == params.output_format;
                              })->first;

        Logger::logger->warn("Deleting all files in directory with file extension '{}'", file_extension);

        auto count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(params.output_dir_path)) {
            if (entry.path().extension() == "." + file_extension) {
                std::filesystem::remove(entry.path());
                count++;
            }
        }

        Logger::logger->warn("Deleted {} files.", count);
    } else {
        Logger::logger->info("Creating output directory '{}'.", params.output_dir_path);
        std::filesystem::create_directories(params.output_dir_path);
    }
}

void FileOutputHandler::writeFile(int iteration, const std::unique_ptr<ParticleContainer>& particle_container) const {
    if (params.output_format == OutputFormat::NONE) {
        return;
    }
    file_writer->writeFile(params, iteration, particle_container);
}

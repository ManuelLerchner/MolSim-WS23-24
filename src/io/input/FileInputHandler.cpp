#include "FileInputHandler.h"

#include <filesystem>
#include <iostream>

#include "io/logger/Logger.h"

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> FileInputHandler::readFile(const std::string& input_file_path,
                                                                                              bool fresh, bool allow_recursion) {
    if (!std::filesystem::exists(input_file_path)) {
        Logger::logger->error("Error: file '{}' does not exist.", input_file_path);
        exit(-1);
    }

    std::string file_extension;

    try {
        file_extension = input_file_path.substr(input_file_path.find_last_of('.'));
    } catch (const std::out_of_range& e) {
        Logger::logger->error("Error: no file extension found.");
        exit(-1);
    }

    if (get_supported_input_file_extensions().find(file_extension) == get_supported_input_file_extensions().end()) {
        Logger::logger->error("Error: file extension '{}' is not supported.", file_extension);
        exit(-1);
    }

    std::unique_ptr<FileReader> file_reader;

    if (file_extension == ".xml") {
        file_reader = std::make_unique<XMLFileReader>(fresh, allow_recursion);
    } else if (file_extension == ".chkpt") {
        file_reader = std::make_unique<ChkptPointFileReader>();
    } else {
        Logger::logger->error("Error: file extension '{}' is not supported.", file_extension);
        exit(-1);
    }

    try {
        auto [particles, config] = file_reader->readFile(input_file_path);
        Logger::logger->info("Loaded {} particles from file {}", particles.size(), input_file_path);
        return std::make_tuple(particles, config);
    } catch (const FileReader::FileFormatException& e) {
        Logger::logger->error("Error: file '{}' is not a valid {} file.", input_file_path, file_extension);
        Logger::logger->error("FileFormatException:\n{}", std::string(e.what()));
        exit(-1);
    }
}

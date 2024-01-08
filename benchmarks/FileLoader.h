#include <io/logger/Logger.h>

#include <filesystem>
#include <string>

#pragma once

class FileLoader {
   public:
    /**
     * @brief Gets the path to the data directory
     *
     * Uses the cmake target_compile_definitions PRIVATE BENCHMARK_DATA_DIR to define the path to the data directory.
     */
    static std::string get_benchmark_data_dir() {
#ifdef BENCHMARK_DATA_DIR
        return BENCHMARK_DATA_DIR;
#else
        throw std::runtime_error("Error: BENCHMARK_DATA_DIR not defined");
#endif
    }

    /**
     * @brief Gets the path to a file in the input directory
     *
     * @param file_name The name of the file
     * @return std::filesystem::path The path to the file
     */
    static std::filesystem::path get_input_file_path(const std::string& file_name) { return {get_benchmark_data_dir() + "/" + file_name}; }
};

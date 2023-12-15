#pragma once

#include "io/input/FileReader.h"
#include "io/input/custom_formats/FileLineReader.h"

/**
 * @brief Class to read particle data from a '.cub' file
 */
class CubFileReader : public FileReader {
   public:
    /**
     * @brief Reads the '.cub' file with the given path and returns a vector of particles
     * (see \ref InputFileFormats "Input File Formats" for details on the .cub file format)
     *
     * @param filepath Path to the file to be read
     */
    [[nodiscard]] std::tuple<std::vector<Particle>, std::optional<SimulationParams>> readFile(
        const std::filesystem::path& filepath) const override;

   private:
    /**
     * @brief Reports an invalid entry in the given file and terminates the full program
     *
     * @param input_file FileLineReader which read the entry
     * @param expected_format Expected format of the entry
     */
    static void checkAndReportInvalidEntry(FileLineReader& input_file, const std::string& expected_format);
};
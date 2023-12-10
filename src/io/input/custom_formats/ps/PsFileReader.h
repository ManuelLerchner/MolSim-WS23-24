#pragma once

#include "io/input/FileReader.h"

/**
 * @brief Class to read particle data from a '.ps' file
 */
class PsFileReader : public FileReader {
   public:
    /**
     * @brief Reads the file with the given path and returns a vector of particles
     * (see \ref InputFileFormats "Input File Formats" for details on the .ps file format).
     *
     * @param filepath Path to the file to be read
     */
    [[nodiscard]] std::tuple<std::vector<Particle>, std::optional<SimulationParams>> readFile(const std::string& filepath) const override;
};

#pragma once

#include "io/input/FileReader.h"
#include "io/xml_schemas/checkpoint/checkpoint_schema.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Class to read particle and simulation data from a '.xml' file
 */
class ChkptPointFileReader : public FileReader {
   public:
    /**
     * @brief Reads particle data from a '.xml' file and returns a vector of particles
     *
     * @param filepath Path to the file to read
     */
    [[nodiscard]] std::tuple<std::vector<Particle>, std::optional<SimulationParams>> readFile(const std::string& filepath) const override;
};
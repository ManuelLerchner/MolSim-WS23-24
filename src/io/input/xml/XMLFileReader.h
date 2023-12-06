#pragma once

#include "io/input/FileReader.h"
#include "io/input/xml/parser/simulation_schema.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Class to read particle and simulation data from a '.xml' file
 */
class XMLFileReader : public FileReader {
   public:
    /**
     * @brief Reads particle data from a '.xml' file and fills the given particle container. Other simulation parameters are returned.
     *
     * @param filepath Path to the file to read
     * @param particle_container Particle container to store the particles in
     * @return optional SimulationParams object containing the simulation parameters given in the file. Unspecified parameters are set to
     * default values.
     */
    [[nodiscard]] std::tuple<std::vector<Particle>, std::optional<SimulationParams>> readFile(const std::string& filepath) const override;
};
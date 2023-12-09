#pragma once

#include "io/output/FileWriter.h"
#include "io/xml_schemas/checkpoint/checkpoint_schema.h"
#include "particles/Particle.h"

/**
 * @brief Class to write particle data to a .chkpt file
 */
class CheckPointWriter : public FileWriter {
   public:
    /**
     * @brief Writes the data of the given ParticleContainer to a .vtu file
     *
     * @param params SimulationParams object which provides the output directory path
     * @param iteration The current iteration number
     * @param particle_container ParticleContainer whose particles are to be written
     */
    virtual void writeFile(const SimulationParams& params, int iteration,
                           const std::unique_ptr<ParticleContainer>& particle_container) const override;

    /**
     * @brief Writes the data of the given vector to a .chkpt file
     *
     * @param params SimulationParams object which provides the output directory path
     * @param iteration The current iteration number
     * @param particles Vector of particles to be written
     */
    virtual std::string writeFile(const SimulationParams& params, int iteration,
                           const std::vector<Particle>& particles) const;
};

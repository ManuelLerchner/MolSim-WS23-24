#pragma once

#include <memory>

#include "particles/containers/ParticleContainer.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Abstract base class for all file writers
 */
class FileWriter {
   public:
    /**
     * @brief virtual destructor for correct cleanup of derived classes
     */
    virtual ~FileWriter() = default;

    /**
     * @brief Writes the file to the given path, uses the given ParticleContainer and the current iteration
     *
     * @param params SimulationParams object which provides the output directory path
     * @param iteration The current iteration number
     * @param particle_container ParticleContainer which provides the data to be written
     */
    virtual void writeFile(const SimulationParams& params, size_t iteration,
                           const std::unique_ptr<ParticleContainer>& particle_container) const = 0;
};
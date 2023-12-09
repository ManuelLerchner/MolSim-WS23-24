#pragma once

#include <fstream>
#include <list>

#include "io/output/FileWriter.h"
#include "particles/Particle.h"
#include "particles/containers/ParticleContainer.h"

/**
 * @brief Class to write particle data to a .xyz file
 */
class XYZWriter : public FileWriter {
   public:
    /**
     * @brief Writes the data of the given ParticleContainer to a .xyz file
     *
     * @param params SimulationParams object which provides the output directory path
     * @param iteration The current iteration
     * @param particle_container ParticleContainer to be used
     */
    virtual void writeFile(const SimulationParams& params, int iteration,
                           const std::unique_ptr<ParticleContainer>& particle_container) const override;
};

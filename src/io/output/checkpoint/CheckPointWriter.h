

#pragma once

#include <list>

#include "io/output/FileWriter.h"
#include "io/output/checkpoint/parser/InternalToXSDTypeAdapter.h"
#include "io/output/checkpoint/parser/checkpoint_schema.h"
#include "particles/Particle.h"

/**
 * @brief Class to write particle data to a .vtk file
 */
class CheckPointWriter : public FileWriter {
   public:
    /**
     * @brief Writes the data of the given ParticleContainer to a .vtk file
     *
     * @param output_dir_path Path to the directory in which to save the output file
     * @param iteration The current iteration number
     * @param particle_container ParticleContainer whose particles are to be written
     */
    void writeFile(const std::string& output_dir_path, int iteration,
                   const std::unique_ptr<ParticleContainer>& particle_container) const override;
};

#pragma once

#include "io/output/FileWriter.h"
#include "io/xml_schemas/vtu_file/vtu_file_schema.h"
#include "particles/Particle.h"

/**
 * @brief Class to write particle data to a .vtu file
 */
class VTUWriter : public FileWriter {
   public:
    /**
     * @brief Writes the data of the given ParticleContainer to a .vtu file
     *
     * @param output_dir_path Path to the directory in which to save the output file
     * @param iteration The current iteration number
     * @param particle_container ParticleContainer whose particles are to be written
     */
    void writeFile(const std::string& output_dir_path, int iteration,
                   const std::unique_ptr<ParticleContainer>& particle_container) const override;

   private:
    /**
     * @brief Creates a VTUFile_t object with the given number of particles.
     *
     * @param numParticles Number of particles to be plotted
     * @return VTUFile_t object with the given number of particles
     */
    [[nodiscard]] static VTUFile_t initializeOutput(int numParticles);

    /**
     * @brief Writes a given particle to the given VTUFile_t object.
     *
     * @param file VTUFile_t object to write to
     * @param p Particle to be written
     */
    static void plotParticle(VTUFile_t& file, const Particle& p);
};

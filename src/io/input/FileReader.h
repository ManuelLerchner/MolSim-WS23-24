#pragma once

#include <string>

#include "containers/DirectSumContainer.h"

/**
 * @brief Abstract base class for all file readers
 */
class FileReader {
   public:
    virtual ~FileReader() = default;

    class FileFormatException : public std::exception {};

    /**
     * @brief Reads the file with the given path and fills the given ParticleContainer with the particle data stored in the file
     * @param filepath Path to the file to be read
     * @param particle_container ParticleContainer to be filled
     */
    virtual void readFile(const std::string& filepath, DirectSumContainer& particle_container) const = 0;
};
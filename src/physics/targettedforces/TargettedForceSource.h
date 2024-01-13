#pragma once

#include <iostream>
#include <vector>

#include "particles/Particle.h"

/**
 * @brief Interface for targetted force source classes
 *
 * Definition of an interface for targetted force source classes.
 * This is used to ensure inheriting classes implement the method applyForce(std::vector<Particle>& particles)
 * according to our definition.
 *
 * A TargettedForceSource specifies the force exerted on a specific particles within a vector, using the index within that vector.
 */
class TargettedForceSource {
   protected:
    /**
     * @brief Indices of the particles on which the force is applied
     */
    std::vector<size_t> target_indices;

   public:
    /**
     *
     */
    inline TargettedForceSource(const std::vector<size_t>& target_indices) : target_indices(target_indices){};

    /**
     * @brief Virtual destructor for correct cleanup of derived classes
     *
     * Virtual destructor to ensure correct deletion of inheriting classes.
     */
    virtual ~TargettedForceSource() = default;

    /**
     * @brief Applies the force directly to the particles with the specified indices within the vector
     *
     * @param particle_vector Particle vector on which the force is applied
     * @param curr_simulation_time Current simulation time
     *
     * Calculates and the force exerted on the particles identified by index within the given particle vector.
     */
    virtual void applyForce(std::vector<Particle>& particle_vector, double curr_simulation_time) const = 0;

    /**
     * @brief Conversion from a force source object to a string containing its name
     */
    virtual explicit operator std::string() const = 0;
};

// overload the << operator for the ForceSource class to allow easier printing
inline std::ostream& operator<<(std::ostream& os, const TargettedForceSource& forceSource) {
    os << static_cast<std::string>(forceSource);
    return os;
}
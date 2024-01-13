#pragma once

#include "physics/pairwiseforces/PairwiseForceSource.h"

/**
 *  @brief Class to calculate the only the repulisve part of the Lennard-Jones force between particles. Implements the interface
 * PairwiseForceSource.
 *
 * Implementation of the force calculation to simulate the repulsive part of Lennard-Jones forces between particles.
 */
class LennardJonesRepulsiveForce : public PairwiseForceSource {
   public:
    /**
     * @brief Calculates only the repulsive part of the Lennard-Jones forces between two particles.
     *
     * @param p Particle
     * @param q Particle
     * @return Repulsive Lennard-Jones force exerted by q on p
     *
     * Calculates the Lennard-Jones force which q exerts on p
     */
    std::array<double, 3UL> calculateForce(Particle& p, Particle& q) const override;

    /**
     * @brief Returns "Lennard-Jones (Repulsive Only)" as name of the force
     */
    explicit operator std::string() const override;
};

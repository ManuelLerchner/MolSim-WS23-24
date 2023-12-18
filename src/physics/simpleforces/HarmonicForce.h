#pragma once

#include "physics/simpleforces/SimpleForceSource.h"

/**
 *  @brief Class to calculate the harmonic force on a particle
 */
class HarmonicForce : public SimpleForceSource {
   public:
    /**
     * @brief Constructor for the GlobalDownwardsGravity class
     */
    explicit HarmonicForce() = default;

    /**
     * @brief Calculates the harmonic force on a particle supplied by all its connected neighbors
     * @param p Particle
     * @return std::array<double, 3UL> Force vector
     */
    std::array<double, 3UL> calculateForce(Particle& p) const override;

    /**
     * @brief Returns "HarmonicForce" as string
     */
    explicit operator std::string() const override;
};

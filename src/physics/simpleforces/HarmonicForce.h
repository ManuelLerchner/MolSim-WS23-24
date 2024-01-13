#pragma once

#include <array>
#include <variant>

#include "physics/simpleforces/SimpleForceSource.h"
#include "simulation/SimulationParams.h"

/**
 *  @brief Class to calculate the harmonic force on a particle
 */
class HarmonicForce : public SimpleForceSource {
    bool is_finite_container;
    std::array<double, 3> domain_size;

   public:
    /**
     * @brief Constructor for the GlobalDownwardsGravity class
     */
    explicit HarmonicForce(const std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType>& container_data);

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

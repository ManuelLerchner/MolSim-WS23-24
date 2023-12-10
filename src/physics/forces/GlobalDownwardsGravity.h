#pragma once

#include "physics/forces/ForceSource.h"

/**
 *  @brief Class to calculate the global downwards gravity force.
 */
class GlobalDownwardsGravity : public ForceSource {
   private:
    double g;

   public:
    /**
     * @brief Constructor for the GlobalDownwardsGravity class
     * @param g Gravitational acceleration
     */
    explicit GlobalDownwardsGravity(double g = -10) : g(g) {}

    /**
     * @brief Sets the gravitational acceleration
     * @param g Gravitational acceleration
     */
    void setGravitationalAcceleration(double g);

    std::array<double, 3UL> calculateForce(Particle& p, Particle& q) const override;

    /**
     * @brief Returns "Gravity" as name of the force
     */
    explicit operator std::string() const override;
};

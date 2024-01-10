#pragma once

#include "physics/pairwiseforces/PairwiseForceSource.h"

/**
 *  @brief Class to calculate the smoothed Lennard-Jones force between particles. Implements the interface PairwiseForceSource.
 *
 * This class behaves similar like the normal Lennard-Jones force, but it is smoothed out between the smoothing radius r_l and the cutoff
 * radius r_c.
 *
 * Implementation of the force calculation to simulate a smooth Lennard-Jones forces between particles.
 */
class SmoothedLennardJonesForce : public PairwiseForceSource {
   public:
    /**
     * @brief Construct a new SmoothedLennardJonesForce object
     *
     * @param r_c cutoff radius
     * @param r_l smoothing radius
     */
    SmoothedLennardJonesForce(double r_c, double r_l) : r_c(r_c), r_l(r_l){};

    /**
     * @brief Calculates the smoothed Lennard-Jones forces between two particles
     *
     * @param p Particle
     * @param q Particle
     * @return smoothed Lennard-Jones force exerted by q on p
     *
     * Calculates the Lennard-Jones force which q exerts on p
     */
    std::array<double, 3UL> calculateForce(Particle& p, Particle& q) const override;

    /**
     * @brief Returns "SmoothedLennardJones" as the name of the force
     */
    explicit operator std::string() const override;

   private:
    /**
     * @brief the radius after which the force is 0
     */
    double r_c;

    /**
     * @brief the radius whithin the normal Lennard-Jones force is applied. Between r_l and r_c the force is smoothed out
     */
    double r_l;
};

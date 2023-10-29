#pragma once

#include "ForceCalculation.h"

/*
 * Implementation of the force calculation to simulate gravity forces between planets.
 * This class implements the interface ForceCalculation.
 */
class GravityCalculation : public ForceCalculation {
   public:
    /*
     * @brief Calculates the forces between the particles in the given container
     * @param p Particle whose force is to be updated
	 * @param q Particle which exerts the force on p
     *
     * Calculates the forces between all particles in the given container and updates their values according to simple
     * gravitational laws of motion. This affects the particles' f and oldF attributes. Before overwrtiting the current
     * force, the old force is saved in the particle's oldF attribute. The previous value of oldF is lost.
     */
    void addForce(Particle& p, Particle& q) override;
};
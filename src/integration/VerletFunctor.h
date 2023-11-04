#pragma once

#include "integration/IntegrationFunctor.h"

/**
 * @brief Implementation of the Strömer-Verlet integration method. Implements the interface IntegrationFunctor.
 *
 * Implements the IntegrationFunctor interface, and therefore updates all particles in the particle_container according to the Verlet
 * integration method.
 */
class VerletFunctor : public IntegrationFunctor {
   public:
    void step(ParticleContainer& particle_container, std::vector<std::unique_ptr<ForceSource>>& force_sources, double delta_t) override;
};
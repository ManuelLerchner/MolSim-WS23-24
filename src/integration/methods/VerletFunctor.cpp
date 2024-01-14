#include "VerletFunctor.h"

#include "utils/ArrayUtils.h"

void VerletFunctor::step(std::unique_ptr<ParticleContainer>& particle_container,
                         const std::vector<std::shared_ptr<SimpleForceSource>>& simple_force_sources,
                         const std::vector<std::shared_ptr<PairwiseForceSource>>& pairwise_force_sources,
                         const std::vector<std::shared_ptr<TargettedForceSource>>& targetted_force_sources, double delta_t,
                         double curr_simulation_time) const {
    for (auto& p : *particle_container) {
        // update position
        if (!p.isLocked()) {
            const std::array<double, 3> new_x = p.getX() + delta_t * p.getV() + (delta_t * delta_t / (2 * p.getM())) * p.getF();
            p.setX(new_x);
        }

        // reset forces
        p.setOldF(p.getF());
        p.setF({0, 0, 0});
    }

    // calculate new forces
    particle_container->prepareForceCalculation();
    particle_container->applySimpleForces(simple_force_sources);
    particle_container->applyPairwiseForces(pairwise_force_sources);
    particle_container->applyTargettedForces(targetted_force_sources, curr_simulation_time);

    // update velocity
    for (auto& p : *particle_container) {
        if (!p.isLocked()) {
            const std::array<double, 3> new_v = p.getV() + (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());
            p.setV(new_v);
        } else {
            p.setV({0, 0, 0});
        }
    }
}

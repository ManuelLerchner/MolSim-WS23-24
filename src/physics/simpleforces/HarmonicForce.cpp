#include "HarmonicForce.h"

#include "particles/Particle.h"
#include "utils/ArrayUtils.h"

std::array<double, 3UL> HarmonicForce::calculateForce(Particle& p) const {
    auto total_harmonic_force = std::array<double, 3UL>{0, 0, 0};

    for (auto& [connected_particle, l_0, k] : p.getConnectedParticles()) {
        if (auto connected_particle_ptr = connected_particle.lock()) {
            const auto displacement = connected_particle_ptr->getX() - p.getX();
            const double dist = ArrayUtils::L2Norm(displacement);

            const auto f_harmonic = (k * (dist - l_0) / dist) * displacement;

            total_harmonic_force = total_harmonic_force + f_harmonic;
        }
    }

    return total_harmonic_force;
}

HarmonicForce::operator std::string() const { return "HarmonicForce"; }

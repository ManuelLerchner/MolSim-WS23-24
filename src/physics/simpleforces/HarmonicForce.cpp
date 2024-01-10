#include "HarmonicForce.h"

#include "particles/Particle.h"
#include "utils/ArrayUtils.h"

std::array<double, 3UL> HarmonicForce::calculateForce(Particle& p) const {
    auto total_harmonic_force = std::array<double, 3UL>{0, 0, 0};

    for (auto& [ptr_diff, l_0, k] : p.getConnectedParticles()) {
        Particle* connected_particle = &p + ptr_diff;
        const auto displacement = connected_particle->getX() - p.getX();
        const double dist = ArrayUtils::L2Norm(displacement);

        const auto f_harmonic = (k * (dist - l_0) / dist) * displacement;

        total_harmonic_force = total_harmonic_force + f_harmonic;
    }

    return total_harmonic_force;
}

HarmonicForce::operator std::string() const { return "HarmonicForce"; }

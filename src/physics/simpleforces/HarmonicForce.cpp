#include "HarmonicForce.h"

#include "particles/Particle.h"
#include "utils/ArrayUtils.h"

HarmonicForce::HarmonicForce(const std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType>& container_data) {
    if (std::holds_alternative<SimulationParams::DirectSumType>(container_data)) {
        is_finite_container = false;
    } else {
        is_finite_container = true;
        domain_size = std::get<SimulationParams::LinkedCellsType>(container_data).domain_size;
    }
}

std::array<double, 3UL> HarmonicForce::calculateForce(Particle& p) const {
    auto total_harmonic_force = std::array<double, 3UL>{0, 0, 0};

    for (auto& [ptr_diff, l_0, k] : p.getConnectedParticles()) {
        Particle* connected_particle = &p + ptr_diff;
        auto displacement = connected_particle->getX() - p.getX();

        if (is_finite_container) {
            for (size_t i = 0; i < displacement.size(); i++) {
                if (std::abs(displacement[i]) > domain_size[i] * 0.5) {
                    bool is_positive = displacement[i] > 0;
                    if (is_positive) {
                        displacement[i] -= domain_size[i];
                    } else {
                        displacement[i] += domain_size[i];
                    }
                }
            }
        }

        const double dist = ArrayUtils::L2Norm(displacement);

        const auto f_harmonic = (k * (dist - l_0) / dist) * displacement;

        total_harmonic_force = total_harmonic_force + f_harmonic;
    }

    return total_harmonic_force;
}

HarmonicForce::operator std::string() const { return "HarmonicForce"; }

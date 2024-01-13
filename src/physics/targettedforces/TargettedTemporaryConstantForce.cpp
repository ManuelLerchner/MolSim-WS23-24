#include "TargettedTemporaryConstantForce.h"

#include <spdlog/formatter.h>

#include "utils/ArrayUtils.h"

TargettedTemporaryConstantForce::TargettedTemporaryConstantForce(const std::vector<size_t>& targetIndices,
                                                                 const std::array<double, 3UL>& force, double start_time, double end_time)
    : TargettedForceSource(targetIndices), force(force), start_time(start_time), end_time(end_time) {}

void TargettedTemporaryConstantForce::applyForce(std::vector<Particle>& particle_vector, double curr_simulation_time) const {
    if (curr_simulation_time < start_time || curr_simulation_time > end_time) {
        return;
    }

    for (auto& index : target_indices) {
        Particle& particle = particle_vector[index];
        particle.setF(particle.getF() + force);
    }
}

TargettedTemporaryConstantForce::operator std::string() const {
    return fmt::format("TargettedTemporaryConstantForce (start: {}, end: {}, force: [{}, {}, {}])", start_time, end_time, force[0],
                       force[1], force[2]);
}
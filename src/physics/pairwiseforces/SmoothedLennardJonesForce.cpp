#include "SmoothedLennardJonesForce.h"

#include "physics/pairwiseforces/LennardJonesForce.h"
#include "utils/ArrayUtils.h"

std::array<double, 3UL> SmoothedLennardJonesForce::calculateForce(Particle& p, Particle& q) const {
    const auto displacement = q.getX() - p.getX();
    const double dist = ArrayUtils::L2Norm(displacement);

    if (dist <= r_l) {
        static LennardJonesForce lennard_jones_force;
        return lennard_jones_force.calculateForce(p, q);
    } else if (dist <= r_c) {
        const double sigma = (p.getSigma() + q.getSigma()) / 2;
        const double epsilon = std::sqrt(p.getEpsilon() * q.getEpsilon());

        const double sigma_pow_6 = std::pow(sigma, 6);
        const double dist_pow_6 = std::pow(dist, 6);

        const auto f_smoothed_lennard_jones =
            (-24 * sigma_pow_6 * epsilon) / (std::pow(dist, 14) * std::pow(r_c - r_l, 3)) * (r_c - dist) *
            (r_c * r_c * (2 * sigma_pow_6 - dist_pow_6) + r_c * (3 * r_l - dist) * (dist_pow_6 - 2 * sigma_pow_6) +
             dist * (5 * r_l * sigma_pow_6 - 2 * r_l * dist_pow_6 - 3 * sigma_pow_6 * dist + std::pow(dist, 7))) *
            displacement;

        return f_smoothed_lennard_jones;
    } else {
        return {0, 0, 0};
    }
};

SmoothedLennardJonesForce::operator std::string() const { return "SmoothedLennardJones"; };
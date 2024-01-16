#include "LennardJonesForce.h"

#include "utils/ArrayUtils.h"

std::array<double, 3UL> LennardJonesForce::calculateForce(Particle& p, Particle& q) const {
    const auto displacement = q.getX() - p.getX();
    const double distSq = ArrayUtils::L2NormSquared(displacement);

    const double sigma = (p.getSigma() + q.getSigma()) / 2;
    const double epsilon = std::sqrt(p.getEpsilon() * q.getEpsilon());

    const double sigma_dist_pow_6 = std::pow(sigma * sigma / distSq, 3);

    const auto f_lennard_jones = (24 * epsilon / distSq) * (sigma_dist_pow_6 - 2 * std::pow(sigma_dist_pow_6, 2)) * displacement;

    return f_lennard_jones;
};

LennardJonesForce::operator std::string() const { return "Lennard-Jones"; };
#include "LennardJonesForce.h"

#include "utils/ArrayUtils.h"

std::array<double, 3UL> LennardJonesForce::calculateForce(Particle& p, Particle& q) {
    double epsilon = 5.0;
    double sigma = 1.0;

    double dist = ArrayUtils::L2Norm(p.getX() - q.getX());

    auto f_lennard_jones = (24 * epsilon / (std::pow(dist, 2))) *
                           (std::pow(sigma / dist, 6) - 2 * std::pow(sigma / dist, 12)) * (q.getX() - p.getX());

    return f_lennard_jones;
};
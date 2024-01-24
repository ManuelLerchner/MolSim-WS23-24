#include "LennardJonesRepulsiveForce.h"

#include "utils/ArrayUtils.h"

std::array<double, 3UL> LennardJonesRepulsiveForce::calculateForce(const Particle& p, const Particle& q) const {
    const auto displacement = q.getX() - p.getX();
    const double dist = ArrayUtils::L2Norm(displacement);
    const double sigma = (p.getSigma() + q.getSigma()) / 2;

    if (dist > std::pow(2, 1.0 / 6.0) * sigma) return std::array<double, 3UL>{0, 0, 0};

    const double epsilon = std::sqrt(p.getEpsilon() * q.getEpsilon());

    const auto f_lennard_jones =
        (24 * epsilon / (std::pow(dist, 2))) * (std::pow(sigma / dist, 6) - 2 * std::pow(sigma / dist, 12)) * displacement;

    return f_lennard_jones;
};

LennardJonesRepulsiveForce::operator std::string() const { return "Lennard-Jones (Repulsive Only)"; };
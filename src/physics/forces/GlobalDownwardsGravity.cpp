#include "GlobalDownwardsGravity.h"

std::array<double, 3UL> GlobalDownwardsGravity::calculateForce(Particle& p, Particle& q) const {
    // this is propably the wrong interface for this force type
    exit(-1);
}

void GlobalDownwardsGravity::setGravitationalAcceleration(double g) { this->g = g; }

GlobalDownwardsGravity::operator std::string() const { return "GlobalDownwardsGravity"; }
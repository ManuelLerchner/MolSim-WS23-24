#include "GlobalDownwardsGravity.h"

GlobalDownwardsGravity::GlobalDownwardsGravity(double g) : g(g) {}

std::array<double, 3UL> GlobalDownwardsGravity::calculateForce(Particle& p) const { return {0.0, -p.getM() * g, 0.0}; }

GlobalDownwardsGravity::operator std::string() const { return "GlobalDownwardsGravity: g=" + std::to_string(g); }

void GlobalDownwardsGravity::setGravitationalAcceleration(double g) { this->g = g; }
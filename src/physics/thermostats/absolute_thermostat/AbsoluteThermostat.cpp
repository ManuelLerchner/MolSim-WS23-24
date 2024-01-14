#include "AbsoluteThermostat.h"

#include <cmath>

#include "utils/ArrayUtils.h"

AbsoluteThermostat::AbsoluteThermostat(double target_temperature, double max_temperature_change, bool third_dimension)
    : Thermostat(target_temperature, max_temperature_change, third_dimension ? 3 : 2) {}

void AbsoluteThermostat::scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const {
    const double current_temperature = getCurrentContainerTemperature(particle_container);
    const double temperature_change = std::min(std::abs(target_temperature - current_temperature), max_temperature_change);
    const double new_temperature = current_temperature + temperature_change * (target_temperature > current_temperature ? 1 : -1);

    const double scaling_factor = std::sqrt(new_temperature / current_temperature);

    for (auto& particle : *particle_container) {
        if (particle.isLocked()) continue;
        particle.setV(scaling_factor * particle.getV());
    }
}

double AbsoluteThermostat::getContainerKineticEnergy(const std::unique_ptr<ParticleContainer>& particle_container) const {
    double total_kinetic_energy = 0;
    for (auto& particle : *particle_container) {
        if (particle.isLocked()) continue;
        std::array<double, 3> v = particle.getV();
        total_kinetic_energy += particle.getM() * (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) * 0.5;
    }
    return total_kinetic_energy;
}

double AbsoluteThermostat::getCurrentContainerTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const {
    return 2 * getContainerKineticEnergy(particle_container) / (dimensions * particle_container->size());
}
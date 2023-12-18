#include "RelativeThermostat.h"

#include <cmath>

#include "utils/ArrayUtils.h"

RelativeThermostat::RelativeThermostat(double target_temperature, double max_temperature_change, bool third_dimension)
    : Thermostat(target_temperature, max_temperature_change, third_dimension ? 3 : 2) {}

std::array<double, 3> averageVelocity(const std::unique_ptr<ParticleContainer>& particle_container) {
    std::array<double, 3> average_velocity = {0, 0, 0};
    for (auto& particle : *particle_container) {
        average_velocity = average_velocity + particle.getV();
    }
    average_velocity = (1.0 / particle_container->size()) * average_velocity;
    return average_velocity;
}

void RelativeThermostat::scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const {
    auto average_velocity = averageVelocity(particle_container);

    for (auto& particle : *particle_container) {
        const double current_temperature = getCurrentTemperature(particle, average_velocity);

        const double temperature_change = std::min(std::abs(target_temperature - current_temperature), max_temperature_change);
        const double new_temperature = current_temperature + temperature_change * (target_temperature > current_temperature ? 1 : -1);

        const double scaling_factor = std::sqrt(new_temperature / current_temperature);

        particle.setV(scaling_factor * particle.getV());
    }
}

double RelativeThermostat::getKineticEnergy(Particle& particle, std::array<double, 3>& average_velocity) const {
    std::array<double, 3> v = particle.getV() - average_velocity;
    return particle.getM() * (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) * 0.5;
}

double RelativeThermostat::getCurrentTemperature(Particle& particle, std::array<double, 3>& average_velocity) const {
    return 2 * getKineticEnergy(particle, average_velocity) / dimensions;
}
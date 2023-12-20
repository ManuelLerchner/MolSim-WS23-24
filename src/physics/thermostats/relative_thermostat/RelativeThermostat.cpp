#include "RelativeThermostat.h"

#include <cmath>

#include "utils/ArrayUtils.h"

RelativeThermostat::RelativeThermostat(double target_temperature, double max_temperature_change, bool third_dimension)
    : Thermostat(target_temperature, max_temperature_change, third_dimension ? 3 : 2) {}

std::array<double, 3> averageVelocity(const std::unique_ptr<ParticleContainer>& particle_container) {
    std::array<double, 3> average_velocity = {0, 0, 0};
    size_t count = 0;
    for (auto& particle : *particle_container) {
        if (particle.isLocked()) continue;
        average_velocity = average_velocity + particle.getV();
        count++;
    }
    average_velocity = (1.0 / count) * average_velocity;
    return average_velocity;
}
void RelativeThermostat::scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const {
    const std::array<double, 3> average_velocity = averageVelocity(particle_container);

    const double current_temperature = getCurrentContainerTemperature(particle_container, average_velocity);
    const double temperature_change = std::min(std::abs(target_temperature - current_temperature), max_temperature_change);
    const double new_temperature = current_temperature + temperature_change * (target_temperature > current_temperature ? 1 : -1);

    const double scaling_factor = std::sqrt(new_temperature / current_temperature);

    for (auto& particle : *particle_container) {
        if (particle.isLocked()) continue;
        particle.setV(average_velocity + scaling_factor * (particle.getV() - average_velocity));
    }
}

double RelativeThermostat::getContainerKineticEnergy(const std::unique_ptr<ParticleContainer>& particle_container,
                                                     std::array<double, 3> average_velocity) const {
    double total_kinetic_energy = 0;
    for (auto& particle : *particle_container) {
        if (particle.isLocked()) continue;
        std::array<double, 3> v = particle.getV() - average_velocity;
        total_kinetic_energy += particle.getM() * (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) * 0.5;
    }
    return total_kinetic_energy;
}

double RelativeThermostat::getCurrentContainerTemperature(const std::unique_ptr<ParticleContainer>& particle_container,
                                                          std::array<double, 3> average_velocity) const {
    return 2 * getContainerKineticEnergy(particle_container, average_velocity) / (dimensions * particle_container->size());
}
#include "Thermostat.h"

#include "io/logger/Logger.h"
#include "utils/ArrayUtils.h"
#include "utils/MaxwellBoltzmannDistribution.h"

Thermostat::Thermostat(double target_temperature, double max_temperature_change, ThirdDimension third_dimension)
    : target_temperature(target_temperature), max_temperature_change(max_temperature_change), third_dimension(third_dimension) {
    if (target_temperature < 0) {
        Logger::logger->error("Target temperature must be positive");
        throw std::runtime_error("Target temperature must be positive");
    }

    if (max_temperature_change < 0) {
        Logger::logger->error("Max temperature change must be an absolute value (positive)");
        throw std::runtime_error("Max temperature change must be an absolute value (positive)");
    }
}

void Thermostat::setParticleTemperature(double new_temperature, Particle& particle, ThirdDimension third_dimension) {
    size_t dimension_count = third_dimension == ThirdDimension::ENABLED ? 3 : 2;

    particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(std::sqrt(new_temperature / particle.getM()), dimension_count));
}

void Thermostat::setTemperature(double new_temperature, const std::unique_ptr<ParticleContainer>& particle_container) {
    size_t dimension_count = third_dimension == ThirdDimension::ENABLED ? 3 : 2;

    for (auto& particle : *particle_container) {
        particle.setV(maxwellBoltzmannDistributedVelocity(std::sqrt(new_temperature / particle.getM()), dimension_count));
    }
}

double Thermostat::getTargetTemperature() const { return target_temperature; }

double Thermostat::getMaxTemperatureChange() const { return max_temperature_change; }

ThirdDimension Thermostat::getThirdDimension() const { return third_dimension; }
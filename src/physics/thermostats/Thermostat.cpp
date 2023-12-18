#include "Thermostat.h"

#include "io/logger/Logger.h"
#include "utils/ArrayUtils.h"
#include "utils/MaxwellBoltzmannDistribution.h"

void Thermostat::setParticleTemperature(double new_temperature, Particle& particle, size_t dimensions) {
    if (dimensions < 2 || dimensions > 3) {
        Logger::logger->error("Invalid number of dimensions: {}. Must be 2 or 3.", dimensions);
        throw std::runtime_error("Invalid number of dimensions");
    }

    particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(std::sqrt(new_temperature / particle.getM()), dimensions));
}

void Thermostat::setTemperature(double new_temperature, const std::unique_ptr<ParticleContainer>& particle_container) {
    if (dimensions < 2 || dimensions > 3) {
        Logger::logger->error("Invalid number of dimensions: {}. Must be 2 or 3.", dimensions);
        throw std::runtime_error("Invalid number of dimensions");
    }

    for (auto& particle : *particle_container) {
        particle.setV(maxwellBoltzmannDistributedVelocity(std::sqrt(new_temperature / particle.getM()), dimensions));
    }
}

double Thermostat::getTargetTemperature() const { return target_temperature; }

double Thermostat::getMaxTemperatureChange() const { return max_temperature_change; }

size_t Thermostat::getDimensions() const { return dimensions; }
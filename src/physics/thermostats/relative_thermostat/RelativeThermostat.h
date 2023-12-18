#pragma once

#include <limits>
#include <memory>

#include "particles/containers/ParticleContainer.h"
#include "physics/thermostats/Thermostat.h"

/**
 * @brief A relative thermostat that can be used to control the temperature of a particle container. Allows for gradual scaling of the
 * temperature towards a set target.
 *
 * @details This thermostat is a basic implementation of the Thermostat interface.
 *
 * This Thermostats is "relative" in the sense that it takes the actual "average" velocity of the particles into account when scaling the
 temperature.
 * This means that the particles jiggle gets reduced, but in total the particles will still move if given an initial velocity.
 */
class RelativeThermostat : public Thermostat {
   public:
    /**
     * @brief Construct a new Thermostat object.
     *
     * @param target_temperature The target temperature for thermostat applications.
     * @param max_temperature_change The maximum temperature change allowed per thermostat application.
     * @param third_dimension True if the thermostat applies to a 3-dimensional domain, false for 2 dimensions.
     */
    RelativeThermostat(double target_temperature, double max_temperature_change = std::numeric_limits<double>::max(),
                       bool third_dimension = true);

    /**
     * @brief Scale the temperature of a particle container towards the target temperature. Capped by the maximum temperature change.
     *
     * @param particle_container The particle container to scale the temperature of.
     */
    void scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const override;

    /**
     * @brief Get the kinetic energy of a particle.
     *
     * @param particle The particle to get the kinetic energy of.
     * @param average_velocity The average velocity of all particles in the container.
     * @return double The kinetic energy of the particle.
     */
    double getKineticEnergy(Particle& particle, std::array<double, 3>& average_velocity) const;

    /**
     * @brief Get the current temperature of a particle
     *
     * @param particle The particle to get the temperature of.
     * @param average_velocity The average velocity of all particles in the container.
     */
    double getCurrentTemperature(Particle& particle, std::array<double, 3>& average_velocity) const;
};
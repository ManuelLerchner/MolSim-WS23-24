#pragma once

#include <limits>
#include <memory>

#include "particles/containers/ParticleContainer.h"
#include "physics/thermostats/Thermostat.h"

/**
 * @brief A basic thermostat that can be used to control the temperature of a particle container. Allows for gradual scaling of the
 * temperature towards a set target.
 *
 * @details This thermostat is a basic implementation of the Thermostat interface.
 *
 * This Thermostats is "absolute" in the sense that it does not take the actual velocity of the particles into account when scaling the
 * temperature. It simply freezes the particles until they are no longer moving, even if they have an initial velocity.
 */
class AbsoluteThermostat : public Thermostat {
   public:
    /**
     * @brief Construct a new Thermostat object.
     *
     * @param target_temperature The target temperature for thermostat applications.
     * @param max_temperature_change The maximum temperature change allowed per thermostat application.
     * @param third_dimension True if the thermostat applies to a 3-dimensional domain, false for 2 dimensions.
     */
    AbsoluteThermostat(double target_temperature, double max_temperature_change = std::numeric_limits<double>::max(),
                       bool third_dimension = true);

    /**
     * @brief Scale the temperature of a particle container towards the target temperature. Capped by the maximum temperature change.
     *
     * @param particle_container The particle container to scale the temperature of.
     */
    void scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const override;

    /**
     * @brief Get the kinetic energy of all particles in a particle container.
     *
     * @param particle_container The particle container to get the kinetic energy of.
     * @return double The total kinetic energy of all particles in the container.
     */
    double getContainerKineticEnergy(const std::unique_ptr<ParticleContainer>& particle_container) const;

    /**
     * @brief Get the current temperature of a particle container.
     *
     * @param particle_container The particle container to get the temperature of.
     * @return double The current temperature of the particle container.
     */
    double getCurrentContainerTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const override;
};
#pragma once

#include <limits>
#include <memory>

#include "particles/containers/ParticleContainer.h"
#include "utils/Enums.h"

/**
 * @brief A thermostat that can be used to control the temperature of a particle container. Allows for gradual scaling of the temperature
 * towards a set target.
 */
class Thermostat {
   public:
    /**
     * @brief Construct a new Thermostat object.
     *
     * @param target_temperature The target temperature for thermostat applications.
     * @param max_temperature_change The maximum temperature change allowed per thermostat application.
     * @param third_dimension Wether the third dimension is enabled or not.
     */
    explicit Thermostat(double target_temperature, double max_temperature_change, ThirdDimension third_dimension);

    /**
     * @brief Destroy the Thermostat object.
     */
    virtual ~Thermostat() = default;

    /**
     * @brief Scale the temperature of a particle container towards the target temperature. Capped by the maximum temperature change.
     *
     * @param particle_container The particle container to scale the temperature of.
     */
    virtual void scaleTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const = 0;

    /**
     * @brief Get the current temperature of a particle container.
     *
     * @param particle_container The particle container to get the temperature of.
     * @return double The current temperature of the particle container.
     */
    virtual double getCurrentContainerTemperature(const std::unique_ptr<ParticleContainer>& particle_container) const = 0;

    /**
     * @brief Set the initial temperature of a particle container. This function sets the velocity of all particles in the container to a
     * random value according to the Maxwell-Boltzmann distribution (all previous velocities are discarded).
     * Use this function for systems with no initial velocity.
     *
     * @param new_temperature The new temperature of the particle container.
     * @param particle_container The particle container to set the initial temperature of.
     */
    void setTemperature(double new_temperature, const std::unique_ptr<ParticleContainer>& particle_container);

    /**
     * @brief Set the temperature of a particle. This method adds a random velocity to the particle according to the Maxwell-Boltzmann
     * distribution. This function can be used for particle generators since previous velocities are not discarded.
     *
     * @param new_temperature The new temperature of the particle.
     * @param particle The particle to set the initial temperature of.
     * @param third_dimension Wether the third dimension is enabled or not.
     */
    static void setParticleTemperature(double new_temperature, Particle& particle, ThirdDimension third_dimension);

    /**
     * @brief Get the target temperature of the thermostat.
     *
     * @return double The target temperature of the thermostat.
     */
    [[nodiscard]] double getTargetTemperature() const;

    /**
     * @brief Get the maximum temperature change of the thermostat.
     *
     * @return double The maximum temperature change of the thermostat.
     */
    [[nodiscard]] double getMaxTemperatureChange() const;

    /**
     * @brief Get if the third dimension is enabled on this thermostat or not.
     *
     * @return ThirdDimension
     */
    [[nodiscard]] ThirdDimension getThirdDimension() const;

   protected:
    /**
     * @brief The target temperature for thermostat applications.
     */
    const double target_temperature;

    /**
     * @brief The maximum temperature change allowed per thermostat application.
     */
    const double max_temperature_change;

    /**
     * @brief Defines whether the third dimension is enabled
     */
    const ThirdDimension third_dimension;
};
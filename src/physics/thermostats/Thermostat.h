#pragma once

#include <limits>
#include <memory>

#include "particles/containers/ParticleContainer.h"

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
     * @param dimensions The number of dimensions of the particle container that is going to be used.
     */
    explicit Thermostat(double target_temperature, double max_temperature_change, size_t dimensions);

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
     * @param dimensions The number of dimensions of the particle container.
     */
    static void setParticleTemperature(double new_temperature, Particle& particle, size_t dimensions);

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
     * @brief Get the number of dimensions of expected to be used.
     *
     * @return size_t The number of dimensions of expected to be used.
     */
    [[nodiscard]] size_t getDimensions() const;

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
     * @brief The number of dimensions of the particle container that is going to be used.
     */
    const size_t dimensions;
};
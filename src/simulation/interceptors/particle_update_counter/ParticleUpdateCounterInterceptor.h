#pragma once

#include <chrono>

#include "simulation/interceptors/SimulationInterceptor.h"

class ParticleUpdateCounterInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Thermostat Interceptor object
     */
    ParticleUpdateCounterInterceptor() = default;

    /**
     * @brief This function is sets the particle_updates to 0 and initializes
     * the start time of the simulation
     */
    void onSimulationStart() override;

    /**
     * @brief This function is called on every nth iteration. It counts the
     * number of particle updates which have been performed.
     *
     * @param iteration The current iteration
     */
    void operator()(size_t iteration) override;

    /**
     * @brief This function is empty as the thermostat doesnt need to do anything
     * at the end of the simulation
     *
     * @param iteration The current iteration
     */
    void onSimulationEnd(size_t iteration) override;

    /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    explicit operator std::string() const override;

    /**
     * @brief Get the particle updates per second
     *
     * @return double
     */
    [[nodiscard]] double getParticleUpdatesPerSecond() const;

    /**
     * @brief Get the duration of the simulation
     *
     * @return std::chrono::milliseconds::rep of the duration
     */
    [[nodiscard]] std::chrono::milliseconds::rep getSimulationDurationMS() const;

   private:
    size_t particle_updates = 0;
    std::chrono::high_resolution_clock::time_point t_start;
    std::chrono::high_resolution_clock::time_point t_end;
    std::chrono::milliseconds::rep t_diff{};
    double particle_updates_per_second{};
};
#pragma once
#include <chrono>

#include "simulation/interceptors/SimulationInterceptor.h"

class ThermostatInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Thermostat Interceptor object
     */
    explicit ThermostatInterceptor(Simulation& simulation);

    /**
     * @brief This function is empty as the thermostat doesnt need initialization
     */
    void onSimulationStart() override;

    /**
     * @brief This function is called on every nth iteration. It scales the
     * temperature of the particles in accordance with the thermostat.
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
};
#pragma once
#include <chrono>

#include "simulation/interceptors/SimulationInterceptor.h"

class ThermostatInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Thermostat Interceptor object
     */
    ThermostatInterceptor(Simulation& simulation);

    /**
     * @brief This function is empty as the thermostat doesnt need initialization
     */
    void onSimulationStart();

    /**
     * @brief This function is called on every nth iteration. It scales the
     * temperature of the particles in accordance with the thermostat.
     *
     * @param iteration The current iteration
     */
    void operator()(int iteration);

    /**
     * @brief This function is empty as the thermostat doesnt need to do anything
     * at the end of the simulation
     *
     * @param iteration The current iteration
     */
    void onSimulationEnd(int iteration);

    /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    operator std::string() const;

   private:
    size_t file_counter = 0;
};
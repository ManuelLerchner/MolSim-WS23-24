#pragma once
#include <chrono>

#include "particles/Particle.h"
#include "simulation/interceptors/SimulationInterceptor.h"

class ProgressBarInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Progress Bar Interceptor object
     */
    ProgressBarInterceptor(Simulation& simulation);

    /**
     * @brief This function initalized the start time of the simulation
     * and the previous time point
     */
    void onSimulationStart();

    /**
     * @brief This function is called on every nth iteration. It prints a progress
     * bar to the console and updates the previous time point.
     *
     * @param iteration The current iteration
     */
    void operator()(int iteration);

    /**
     * @brief This function is empty as the progress bar doesnt need to do anything
     * at the end of the simulation
     *
     * @param iteration The current iteration
     */
    void onSimulationEnd(int iteration);

    operator std::string() const;

   private:
    size_t expected_iterations;
    std::chrono::high_resolution_clock::time_point t_start;
    std::chrono::high_resolution_clock::time_point t_prev;
};
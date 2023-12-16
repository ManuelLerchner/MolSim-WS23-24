#pragma once

#include <chrono>
#include <cstddef>

#include "particles/containers/ParticleContainer.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Class to store some overview data of an executed simulation
 */
class SimulationOverview {
   public:
    /**
     * @brief Original simulation parameters bevore the simulation
     */
    SimulationParams params;

    /**
     * @brief Total time the simulation took to execute in seconds (includes time for writing output files and logging)
     */
    double total_time_seconds;

    /**
     * @brief Average time the simulation took to execute per iteration in milliseconds (includes time for writing output files and logging)
     */
    double average_time_per_iteration_millis;

    /**
     * @brief Total number of iterations the simulation ran for (includes an initial force calculation)
     */
    size_t total_iterations;

    /**
     * @brief Summary of the interceptors that were used during the simulation
     */
    std::vector<std::string> interceptor_summaries;

    /**
     * @brief Resulting particles after the simulation
     */
    std::vector<Particle> resulting_particles;

    /**
     * @brief Prints a summary of the simulation overview to the logger
     * @param depth determines the indentation of the log message
     */
    void logSummary(int depth = 0) const;
};
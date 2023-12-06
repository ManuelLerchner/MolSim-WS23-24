#pragma once

#include <chrono>
#include <cstddef>

#include "particles/containers/ParticleContainer.h"

/**
 * @brief Class to store some overview data of an executed simulation
 */
class SimulationOverview {
   public:
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
     * @brief Number of output files written
     */
    size_t files_written;

    /**
     * @brief Resulting particles after the simulation
     */
    std::vector<Particle> resulting_particles;
};
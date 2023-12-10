#pragma once

#include <vector>

#include "integration/IntegrationFunctor.h"
#include "io/output/FileOutputHandler.h"
#include "particles/Particle.h"
#include "particles/containers/ParticleContainer.h"
#include "simulation/SimulationOverview.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Class to run a simulation
 *
 * This class collects all the components needed to run a simulation, and provides a method to run it.
 */
class Simulation {
    /**
     * @brief Reference to the output handler used for writing the output files
     */
    const FileOutputHandler file_output_handler;

    /**
     * @brief Reference to the simulation parameters object
     */
    const SimulationParams& params;

    /**
     * @brief Reference to the `ParticleContainer` on whose content the simulation is performed
     */
    std::unique_ptr<ParticleContainer> particles_container;

    /**
     * @brief Functor used to integrate the particles
     */
    std::unique_ptr<IntegrationFunctor> integration_functor;

   public:
    enum class IntegrationMethod { VERLET };

    /**
     * @brief Construct a new Simulation object and initialize all the necessary components
     *
     * @param particles Reference to the `ParticleContainer` on whose content the simulation is performed
     * @param params Parameters for the simulation. See the class `SimulationParams` for more information
     * @param integration_method The integration method to use for the simulation (Default: `IntegrationMethod::VERLET`)
     */
    Simulation(const std::vector<Particle>& particles, const SimulationParams& params,
               IntegrationMethod integration_method = IntegrationMethod::VERLET);

    /**
     * @brief Runs the simulation, using the parameters given at construction and returns a `SimulationOverview` object containing some data
     *
     * @return SimulationOverview object containing some data about the simulation performed
     */
    SimulationOverview runSimulation();

    /**
     * @brief Runs the simulation without any output for logging- or vtu/xyz-files, using the parameters given at construction and returns a
     * `SimulationOverview` object containing some data
     *
     * @return SimulationOverview object containing some data about the simulation performed
     */
    SimulationOverview runSimulationPerfTest();

   private:
    static void savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params, size_t num_particles);
};
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
     * @brief Time step per iteration. This specifies the accuracy of the simulation
     */
    const double delta_t;

    /**
     * @brief End time of the simulation. Upon reaching this time, the simulation will stop
     */
    const double simulation_end_time;

    /**
     * @brief Reference to the output handler used for writing the output files
     */
    const FileOutputHandler file_output_handler;

    /**
     * @brief Frames per second at which to save the simulation. This is used to calculate how often to save the simulation data
     */
    const int fps;

    /**
     * @brief Length of the simulation video in seconds. This is used to calculate how often to save the simulation data
     */
    const int video_length;

    /**
     * @brief Reference to the simulation parameters object
     */
    const SimulationParams& simulation_params;

    /**
     * @brief Vector of force sources which are used to calculate the new forces
     */
    const std::vector<std::shared_ptr<ForceSource>> forces;

    /**
     * @brief Reference to the `ParticleContainer` on whose content the simulation is performed
     */
    std::unique_ptr<ParticleContainer> particles;

    std::unique_ptr<IntegrationFunctor> integration_functor;

   public:
    enum class IntegrationMethod { VERLET };

    /**
     * @brief Construct a new Simulation object and initialize all the necessary components
     *
     * @param particles Reference to the `ParticleContainer` on whose content the simulation is performed
     * @param simulation_params Parameters for the simulation. See the class `SimulationParams` for more information
     * @param integration_method The integration method to use for the simulation (Default: `IntegrationMethod::VERLET`)
     */
    Simulation(const std::vector<Particle>& particles, const SimulationParams& simulation_params,
               IntegrationMethod integration_method = IntegrationMethod::VERLET);

    /**
     * @brief Runs the simulation, using the parameters given at construction and returns a `SimulationOverview` object containing some data
     *
     * @return SimulationOverview object containing some data about the simulation performed
     */
    SimulationOverview runSimulation();

    /**
     * @brief Runs the simulation without any output for logging- or vtk/xyz-files, using the parameters given at construction and returns a
     * `SimulationOverview` object containing some data
     *
     * @return SimulationOverview object containing some data about the simulation performed
     */
    SimulationOverview runSimulationPerfTest();

   private:
    void savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params, size_t num_particles) const;
};
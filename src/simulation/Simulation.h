#pragma once

#include <memory>
#include <vector>

#include "integration/IntegrationFunctor.h"
#include "io/output/FileOutputHandler.h"
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
     * @brief Reference to the `ParticleContainer` on whose content the simulation is performed
     */
    std::unique_ptr<ParticleContainer>& particles;

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
     * @brief Vector of forces which are applied in the simulation
     */
    const std::vector<std::unique_ptr<ForceSource>>& forces;

    /**
     * @brief Integration functor used to integrate the particles
     */
    std::unique_ptr<IntegrationFunctor> integration_functor;

    /**
     * @brief Thermostat used to control the temperature of the simulation
    */
    Thermostat& thermostat;

   public:
    enum class IntegrationMethod { VERLET };

    /**
     * @brief Construct a new Simulation object and initialize all the necessary components
     *
     * @param particles Reference to the `ParticleContainer` on whose content the simulation is performed
     * @param forces Vector of forces which are applied in the simulation
     * @param simulation_params Parameters for the simulation. See the class `SimulationParams` for more information
     * @param integration_method The integration method to use for the simulation (Default: `IntegrationMethod::VERLET`)
     */
    Simulation(std::unique_ptr<ParticleContainer>& particles, const std::vector<std::unique_ptr<ForceSource>>& forces,
               SimulationParams& simulation_params, IntegrationMethod integration_method = IntegrationMethod::VERLET);

    /**
     * @brief Runs the simulation, using the parameters given at construction and returns a `SimulationOverview` object containing some data
     *
     * @return SimulationOverview object containing some data about the simulation performed
     */
    SimulationOverview runSimulation() const;
};
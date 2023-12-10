#include "io/cli/CLIParser.h"
#include "io/input/FileInputHandler.h"
#include "simulation/Simulation.h"
#include "simulation/SimulationParams.h"

int main(int argc, char* argsv[]) {
    // Parse CLI arguments
    SimulationParams params_cli = parse_arguments(argc, argsv);

    // Parse input file
    auto [initial_particles, simulation_arguments] = FileInputHandler::readFile(params_cli.input_file_path, params_cli.fresh);

    // Combine parameters from CLI and input file
    SimulationParams params = merge_parameters(std::move(params_cli), std::move(simulation_arguments));
    params.num_particles = initial_particles.size();

    // Initialize simulation
    Simulation simulation{initial_particles, params};

    // Print simulation info
    params.logSummary();

    // Run simulation
    auto overview = [&params](Simulation& simulation) {
        if (params.performance_test) {
            return simulation.runSimulationPerfTest();
        } else {
            return simulation.runSimulation();
        }
    }(simulation);

    // Print simulation overview
    overview.logSummary();

    return 0;
}

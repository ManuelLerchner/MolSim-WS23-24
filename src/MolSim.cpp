#include <numeric>

#include "io/cli/CLIParser.h"
#include "io/input/FileInputHandler.h"
#include "io/logger/Logger.h"
#include "particles/containers/ParticleContainer.h"
#include "physics/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "simulation/SimulationOverview.h"
#include "simulation/SimulationParams.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "utils/FormatTime.h"

const std::string ansi_blue_bold = "\e[34m\e[1m";
const std::string ansi_yellow_bold = "\e[33m\e[1m";
const std::string ansi_bright_white_bold = "\e[97m\e[1m";
const std::string ansi_end = "\e[0m";

void print_simulation_input(const SimulationParams& simulation_params, size_t num_particles,
                            const std::vector<std::unique_ptr<ForceSource>>& forces);

void print_simulation_overview(const SimulationOverview& overview);

int main(int argc, char* argsv[]) {
    // Parse CLI arguments
    SimulationParams params_cli = parse_arguments(argc, argsv);

    // Parse input file
    auto [initial_particles, simulation_arguments] = FileInputHandler::readFile(params_cli.input_file_path);

    // Combine parameters from CLI and input file
    SimulationParams simulation_params = merge_parameters(params_cli, simulation_arguments);

    // Create all force sources acting on the particles
    std::vector<std::unique_ptr<ForceSource>> forces;
    forces.push_back(std::make_unique<LennardJonesForce>());

    // Initialize simulation
    Simulation simulation{initial_particles, forces, simulation_params};

    // Print simulation info
    print_simulation_input(simulation_params, initial_particles.size(), forces);

    // Run simulation
    SimulationOverview overview;
    if (simulation_params.performance_test) {
        overview = simulation.runSimulationPerfTest();

    } else {
        overview = simulation.runSimulation();
    }

    // Print simulation info again (for convenience)
    print_simulation_input(simulation_params, initial_particles.size(), forces);

    // Print simulation overview
    print_simulation_overview(overview);

    return 0;
}

void print_simulation_input(const SimulationParams& simulation_params, size_t num_particles,
                            const std::vector<std::unique_ptr<ForceSource>>& forces) {
    // Print Simulation arguments

    Logger::logger->info(ansi_bright_white_bold + "════════════════════════════════════════" + ansi_end);
    Logger::logger->info(ansi_blue_bold + "Simulation input" + ansi_end);
    Logger::logger->info("");
    Logger::logger->info(ansi_yellow_bold + "Simulation arguments:" + ansi_end);
    Logger::logger->info("  Input file path: {}", simulation_params.input_file_path);
    Logger::logger->info("  Output directory path: {}", simulation_params.output_dir_path);
    Logger::logger->info("  Delta_t: {}", simulation_params.delta_t);
    Logger::logger->info("  End_time: {}", simulation_params.end_time);

    Logger::logger->info(ansi_yellow_bold + "Rendering arguments:" + ansi_end);
    Logger::logger->info("  Frames per second: {}", simulation_params.fps);
    Logger::logger->info("  Video length: {}", simulation_params.video_length);

    // Print Physical setup
    Logger::logger->info(ansi_yellow_bold + "Physical setup:" + ansi_end);
    Logger::logger->info("  Number of particles: {}", num_particles);
    Logger::logger->info("  Number of forces: {}", forces.size());

    std::string force_names =
        std::accumulate(forces.begin(), forces.end(), std::string{},
                        [](const std::string& acc, const std::unique_ptr<ForceSource>& force) { return acc + std::string(*force) + ", "; });

    Logger::logger->info("  Forces: {}", force_names);

    Logger::logger->info(ansi_yellow_bold + "Container:" + ansi_end);
    if (std::holds_alternative<SimulationParams::LinkedCellsType>(simulation_params.container_type)) {
        auto lc_container = std::get<SimulationParams::LinkedCellsType>(simulation_params.container_type);

        auto domain_size = lc_container.domain_size;
        Logger::logger->info("  Linked Cells");
        Logger::logger->info("  Domain size: {} x {} x {}", domain_size[0], domain_size[1], domain_size[2]);
        Logger::logger->info("  Cutoff radius: {}", lc_container.cutoff_radius);
        Logger::logger->info("  Boundary conditions: ");
        Logger::logger->info("    Left: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[0]));
        Logger::logger->info("    Right: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[1]));
        Logger::logger->info("    Bottom: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[2]));
        Logger::logger->info("    Top: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[3]));
        Logger::logger->info("    Back: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[4]));
        Logger::logger->info("    Front: {}", LinkedCellsContainer::boundaryConditionToString(lc_container.boundary_conditions[5]));
    } else if (std::holds_alternative<SimulationParams::DirectSumType>(simulation_params.container_type)) {
        Logger::logger->info("  Direct Sum");
    } else {
        Logger::logger->error("Unknown container type");
        exit(-1);
    }

    Logger::logger->info(ansi_bright_white_bold + "════════════════════════════════════════" + ansi_end);
}

void print_simulation_overview(const SimulationOverview& overview) {
    Logger::logger->info(ansi_bright_white_bold + "════════════════════════════════════════" + ansi_end);

    Logger::logger->info(ansi_yellow_bold + "Simulation overview:" + ansi_end);
    Logger::logger->info("  Simulation time: {}", format_seconds_total(overview.total_time_seconds));
    Logger::logger->info("  Number of iterations: {}", overview.total_iterations);
    Logger::logger->info("  Average iteration time: {:.3f}ms", overview.average_time_per_iteration_millis);
    Logger::logger->info("  Number of files written: {}", overview.files_written);
    Logger::logger->info("  Number of particles left: {}", overview.resulting_particles.size());

    Logger::logger->info(ansi_bright_white_bold + "════════════════════════════════════════" + ansi_end);
}
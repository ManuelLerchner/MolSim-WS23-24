#include <array>
#include <memory>

#include "../FileLoader.h"
#include "io/input/FileInputHandler.h"
#include "io/logger/Logger.h"
#include "io/output/FileOutputHandler.h"
#include "particles/containers/ParticleContainer.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "physics/pairwiseforces/GravitationalForce.h"
#include "physics/pairwiseforces/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "utils/ArrayUtils.h"

void execute2DRectBenchmark(int rect_width, int rect_height, double spacing, double lc_cutoff) {
    Logger::logger->set_level(spdlog::level::info);
    Logger::logger->info("Starting 2DRect-benchmark. Dimensions {}x{}...", rect_width, rect_height);

    // Parse input file
    auto [initial_particles, simulation_arguments] =
        FileInputHandler::readFile(FileLoader::get_input_file_path("2DParticleRect/BenchmarkRectFrame.xml"), true);

    // Settings for the Linked Cells Container simulation
    std::array<double, 3> domain_size = {300, 300, 3};
    std::array<LinkedCellsContainer::BoundaryCondition, 6> boundary_conditions = {
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE,
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE,
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE};

    // Settings for the Cuboid spawner for both simulations
    std::array<double, 3> center_offset = {domain_size[0] / 2, domain_size[1] / 2, domain_size[2] / 2};
    CuboidSpawner spawner(center_offset - std::array<double, 3>{rect_width * spacing / 2, rect_height * spacing / 2, 0},
                          {rect_width, rect_height, 1}, spacing, 1, {0, 0, 0}, 0);

    // ############################################################
    // # Direct Sum Container
    // ############################################################

    std::vector<Particle> particles_ds;
    spawner.spawnParticles(particles_ds);

    // Instantiation of the Direct Sum Container simulation

    SimulationParams params_ds{*simulation_arguments};

    params_ds.num_particles = particles_ds.size();

    Simulation simulation_ds(particles_ds, params_ds);

    // Simulating with Direct Sum Container
    params_ds.logSummary();
    SimulationOverview direct_sum_data = simulation_ds.runSimulation();
    direct_sum_data.logSummary();
    direct_sum_data.savePerformanceDataCSV("DirectSum" + std::to_string(rect_width) + "x" + std::to_string(rect_height));

    // ############################################################
    // # Linked Cells Container
    // ############################################################

    std::vector<Particle> particles_lc;
    spawner.spawnParticles(particles_lc);
    // Instantiation of the Linked Cells Container simulation
    SimulationParams params_lc{*simulation_arguments};
    params_lc.container_type = SimulationParams::LinkedCellsType{domain_size, lc_cutoff, boundary_conditions};
    params_lc.num_particles = particles_lc.size();

    Simulation simulation_lc(particles_lc, params_lc);
    // Simulating with Linked Cells Container
    params_lc.logSummary();
    SimulationOverview linked_cells_data = simulation_lc.runSimulation();
    linked_cells_data.logSummary();
    linked_cells_data.savePerformanceDataCSV("LinkedCells" + std::to_string(rect_width) + "x" + std::to_string(rect_height));

    // ############################################################
    // # Comparison Logging
    // ############################################################

    Logger::logger->info("Comparison of Direct Sum and Linked Cells Container:");
    // Ratio between Direct Sum and Linked Cells Container performance
    Logger::logger->info("Runtime Direct Sum: {} s", direct_sum_data.total_time_seconds);
    Logger::logger->info("Runtime Linked Cells: {} s", linked_cells_data.total_time_seconds);
    Logger::logger->info("Performance ratio (DirectSum / LinkedCells): {}",
                         direct_sum_data.total_time_seconds / linked_cells_data.total_time_seconds);
}

/*
 * Creates a 2D particle rect with variable amount of particles and runs the simulation for time measurements.
 * Can be used to compare the performance of the different particle containers.
 */
int main() {
    std::vector<std::pair<int, int>> sizes = {{25, 40}, {50, 40}, {50, 80}, {100, 80}};

    for (auto [size_x, size_y] : sizes) {
        execute2DRectBenchmark(size_x, size_y, 1.1225, 3);
    }

    return 0;
}
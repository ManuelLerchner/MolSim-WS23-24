#include <memory>

#include "io/logger/Logger.h"
#include "io/output/FileOutputHandler.h"
#include "particles/containers/ParticleContainer.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "physics/forces/GravitationalForce.h"
#include "physics/forces/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "utils/ArrayUtils.h"

void execute2DRectBenchmark(int x, int y) {
    Logger::logger->set_level(spdlog::level::info);
    Logger::logger->info("Starting 2DRect-benchmark. Dimensions {}x{}...", x, y);

    std::array<double, 3> domain_size = {300, 300, 3};
    double cutoff_radius = 30;

    std::array<double, 3> center_offset = {domain_size[0] / 2, domain_size[1] / 2, domain_size[2] / 2};

    CuboidSpawner spawner(center_offset - std::array<double, 3>{x * 1.225 / 2, y * 1.225 / 2, 0}, {x, y, 1}, 1.225, 1, {0, 0, 0}, 0);

    std::vector<std::unique_ptr<ForceSource>> forces;
    forces.push_back(std::make_unique<LennardJonesForce>());

    std::unique_ptr<ParticleContainer> particle_container_ds = std::make_unique<DirectSumContainer>();
    spawner.spawnParticles(particle_container_ds);

    SimulationParams params =
        SimulationParams("test_only", "", 0.01, 5, 0, 30, SimulationParams::DirectSumType{}, Thermostat{0, 0, 100000000}, "none");

    Simulation simulation_ds(particle_container_ds, forces, params);

    Logger::logger->info("Starting simulation using Direct Sum container...");
    Logger::logger->set_level(spdlog::level::off);
    SimulationOverview direct_sum_data = simulation_ds.runSimulation();
    Logger::logger->set_level(spdlog::level::info);
    Logger::logger->info("Finished simulation using Direct Sum container\n");

    std::unique_ptr<ParticleContainer> particle_container_lc = std::make_unique<LinkedCellsContainer>(domain_size, cutoff_radius);
    spawner.spawnParticles(particle_container_lc);
    Simulation simulation_lc(particle_container_lc, forces, params);

    Logger::logger->info("Starting simulation using Linked Cells container...");
    Logger::logger->set_level(spdlog::level::off);
    SimulationOverview linked_cells_data = simulation_lc.runSimulation();
    Logger::logger->set_level(spdlog::level::info);
    Logger::logger->info("Finished simulation using Linked Cells container\n");

    Logger::logger->info("Simulation of {} particles in a {}x{} grid\n", x * y, x, y);

    Logger::logger->info("Direct sum container:");
    Logger::logger->info("  Simulation took {:.3f}s", direct_sum_data.total_time_seconds);
    Logger::logger->info("  Total iterations: {}", direct_sum_data.total_iterations);
    Logger::logger->info("  Average time per iteration: {:.3f}ms\n", direct_sum_data.average_time_per_iteration_millis);

    Logger::logger->info("Linked cells container:");
    Logger::logger->info("  Simulation took {:.3f}s", linked_cells_data.total_time_seconds);
    Logger::logger->info("  Total iterations: {}", linked_cells_data.total_iterations);
    Logger::logger->info("  Average time per iteration: {:.3f}ms\n", linked_cells_data.average_time_per_iteration_millis);

    Logger::logger->info("Ratio Linked Cells / Direct Sum: {:.3f}%\n",
                         linked_cells_data.total_time_seconds / direct_sum_data.total_time_seconds * 100);
}

/*
 * Creates a 2D particle rect with variable amount of particles and runs the simulation for time measurements.
 * Can be used to compare the performance of the different particle containers.
 */
int main() {
    execute2DRectBenchmark(25, 40);
    execute2DRectBenchmark(50, 40);
    execute2DRectBenchmark(50, 80);
    execute2DRectBenchmark(100, 80);
    return 0;
}
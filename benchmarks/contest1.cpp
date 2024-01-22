
#include <array>
#include <memory>

#include "io/logger/Logger.h"
#include "io/output/FileOutputHandler.h"
#include "particles/containers/ParticleContainer.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "physics/pairwiseforces/GravitationalForce.h"
#include "physics/pairwiseforces/LennardJonesForce.h"
#include "physics/simpleforces/GlobalDownwardsGravity.h"
#include "physics/thermostats/absolute_thermostat/AbsoluteThermostat.h"
#include "simulation/Simulation.h"
#include "simulation/interceptors/thermostat/ThermostatInterceptor.h"
#include "utils/ArrayUtils.h"

void execute2DRectBenchmark() {
    Logger::logger->set_level(spdlog::level::info);

    // Settings for the Linked Cells Container simulation
    std::array<double, 3> domain_size = {300, 54, 3};
    std::array<LinkedCellsContainer::BoundaryCondition, 6> boundary_conditions = {
        LinkedCellsContainer::BoundaryCondition::PERIODIC,   LinkedCellsContainer::BoundaryCondition::PERIODIC,
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE,
        LinkedCellsContainer::BoundaryCondition::OUTFLOW,    LinkedCellsContainer::BoundaryCondition::OUTFLOW};

    // Settings for the Cuboid spawner of task 2
    CuboidSpawner spawner1({0.6, 2.0, 0.5}, {250, 20, 1}, 1.2, 1.0, {0.0, 0.0, 0.0}, static_cast<int>(0), 1.0, 1.2, false, false, 40);
    CuboidSpawner spawner2({0.6, 27.0, 0.5}, {250, 20, 1}, 1.2, 2.0, {0.0, 0.0, 0.0}, static_cast<int>(1), 1.0, 1.1, false, false, 40);

    std::vector<std::shared_ptr<PairwiseForceSource>> pairwise_forces;
    std::vector<std::shared_ptr<SimpleForceSource>> simple_force_sources;
    pairwise_forces.push_back(std::make_shared<LennardJonesForce>());
    simple_force_sources.push_back(std::make_shared<GlobalDownwardsGravity>(12.44));

    // Set the thermostat:
    std::shared_ptr<Thermostat> thermostat = std::make_shared<AbsoluteThermostat>(40, std::numeric_limits<double>::infinity(), false);
    std::vector<std::shared_ptr<SimulationInterceptor>> simulation_interceptors;
    simulation_interceptors.push_back(std::make_shared<ThermostatInterceptor>(thermostat, 1000));

    std::vector<Particle> particles_lc;
    spawner1.spawnParticles(particles_lc);
    spawner2.spawnParticles(particles_lc);
    // Instantiation of the Linked Cells Container simulation
    SimulationParams params_lc{"2DParticleRect.xml",
                               0.0005,
                               0.5,
                               SimulationParams::LinkedCellsType{domain_size, 2.5, boundary_conditions},
                               simulation_interceptors,
                               simple_force_sources,
                               pairwise_forces,
                               {},
                               false,
                               "./output"};
    params_lc.num_particles = particles_lc.size();
    Simulation simulation_lc(particles_lc, params_lc);
    // Simulating with Linked Cells Container
    params_lc.logSummary();
    SimulationOverview linked_cells_data = simulation_lc.runSimulation();
    linked_cells_data.logSummary();
    linked_cells_data.savePerformanceDataCSV("Contest");
}

int main() {
    execute2DRectBenchmark();
    return 0;
}
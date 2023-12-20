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
#include "simulation/Simulation.h"
#include "utils/ArrayUtils.h"

void execute2DRectBenchmark(int rect_width, int rect_height, double spacing, double lc_cutoff) {
    Logger::logger->set_level(spdlog::level::info);
    Logger::logger->info("Starting 2DRect-benchmark. Dimensions {}x{}...", rect_width, rect_height);

    // Settings for the Linked Cells Container simulation
    std::array<double, 3> domain_size = {300, 300, 3};
    std::array<LinkedCellsContainer::BoundaryCondition, 6> boundary_conditions = {
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE,
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE,
        LinkedCellsContainer::BoundaryCondition::REFLECTIVE, LinkedCellsContainer::BoundaryCondition::REFLECTIVE};

    // Settings for the Cuboid spawner
    std::array<double, 3> center_offset = {domain_size[0] / 2, domain_size[1] / 2, domain_size[2] / 2};
    CuboidSpawner spawner(center_offset - std::array<double, 3>{rect_width * spacing / 2, rect_height * spacing / 2, 0},
                          {rect_width, rect_height, 1}, spacing, 1, {0, 0, 0}, 0);

    std::vector<std::shared_ptr<PairwiseForceSource>> forces;
    forces.push_back(std::make_shared<LennardJonesForce>());

    std::vector<Particle> particles_lc;
    spawner.spawnParticles(particles_lc);
    // Instantiation of the Linked Cells Container simulation
    SimulationParams params_lc{"2DParticleRect.xml",
                               0.01,
                               5,
                               SimulationParams::LinkedCellsType{domain_size, lc_cutoff, boundary_conditions},
                               {},
                               {},
                               forces,
                               true,
                               true};
    params_lc.num_particles = particles_lc.size();
    Simulation simulation_lc(particles_lc, params_lc);
    // Simulating with Linked Cells Container
    params_lc.logSummary();
    SimulationOverview linked_cells_data = simulation_lc.runSimulation();
    linked_cells_data.logSummary();
}

int main() {
    execute2DRectBenchmark(100, 100, 1.1225, 3);
    return 0;
}
#include <gtest/gtest.h>

#include "particles/containers/ParticleContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "physics/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "utils/ArrayUtils.h"

/*
 * Test if the particles of a Lennard-Jones simulation attract each other.
 */
TEST(SimulationRunnerLinkedCells, ParticlesAttractEachother_LennardJones) {
    std::array<double, 3> domain_size = {10, 10, 10};
    double cutoff_radius = 10;
    std::unique_ptr<ParticleContainer> particle_container = std::make_unique<LinkedCellsContainer>(domain_size, cutoff_radius);

    std::array<double, 3> center_offset = {5, 5, 5};

    std::array<double, 3> x1 = {0, 0, 0};
    std::array<double, 3> v1 = {0, 0, 0};

    std::array<double, 3> x2 = {1, 1, 1};
    std::array<double, 3> v2 = {0, 0, 0};

    auto initial_distance = ArrayUtils::L2Norm(x1 - x2);

    double mass = 1;

    auto p1 = Particle(x1 + center_offset, v1, mass, 0);
    auto p2 = Particle(x2 + center_offset, v2, mass, 0);

    particle_container->addParticle(p1);
    particle_container->addParticle(p2);

    FileOutputHandler file_output_handler(FileOutputHandler::OutputFormat::NONE);

    std::vector<std::unique_ptr<ForceSource>> forces;
    forces.push_back(std::make_unique<LennardJonesForce>());

    Simulation simulation(particle_container, forces, file_output_handler, 0.01, 0.1, 0);

    simulation.runSimulation();

    auto new_dist = ArrayUtils::L2Norm((*particle_container)[0].getX() - (*particle_container)[1].getX());

    EXPECT_LT(new_dist, initial_distance);
}
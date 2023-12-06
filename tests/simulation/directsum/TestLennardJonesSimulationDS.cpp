#include <gtest/gtest.h>

#include "particles/containers/ParticleContainer.h"
#include "physics/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "simulation/SimulationUtils.h"
#include "utils/ArrayUtils.h"

/*
 * Test if the particles of a Lennard-Jones simulation attract each other.
 */
TEST(SimulationRunnerDirectSum, ParticlesAttractEachother_LennardJones) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {0, 0, 0};
    std::array<double, 3> v1 = {0, 0, 0};

    std::array<double, 3> x2 = {1, 1, 1};
    std::array<double, 3> v2 = {0, 0, 0};

    auto initial_distance = ArrayUtils::L2Norm(x1 - x2);

    double mass = 1;

    auto p1 = Particle(x1, v1, mass, 0);
    auto p2 = Particle(x2, v2, mass, 0);

    particles.push_back(p1);
    particles.push_back(p2);

    FileOutputHandler file_output_handler(FileOutputHandler::OutputFormat::NONE);

    std::vector<std::unique_ptr<ForceSource>> forces;
    forces.push_back(std::make_unique<LennardJonesForce>());

    SimulationParams params = TEST_DEFAULT_PARAMS;
    params.end_time = 0.1;
    params.delta_t = 0.01;
    Simulation simulation(particles, forces, params);

    auto res = simulation.runSimulation();

    auto new_dist = ArrayUtils::L2Norm((*res.resulting_particles)[0].getX() - (*res.resulting_particles)[1].getX());

    EXPECT_LT(new_dist, initial_distance);
}

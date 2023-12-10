#include <gtest/gtest.h>

#include <memory>

#include "particles/containers/ParticleContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "simulation/Simulation.h"

using BC = LinkedCellsContainer::BoundaryCondition;

/*
 * Test if the particle is deleted at the left boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtLeftBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {2, 5, 5};
    std::array<double, 3> v1 = {-4, 0, 0};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);
    ;

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::OUTFLOW, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

/*
 * Test if the particle is deleted at the right boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtRightBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {8, 5, 5};
    std::array<double, 3> v1 = {4, 0, 0};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::REFLECTIVE, BC::OUTFLOW, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

/*
 * Test if the particle is deleted at the bottom boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtBottomBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {5, 2, 5};
    std::array<double, 3> v1 = {0, -4, 0};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::REFLECTIVE, BC::REFLECTIVE, BC::OUTFLOW, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

/*
 * Test if the particle is deleted at the top boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtTopBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {5, 8, 5};
    std::array<double, 3> v1 = {0, 4, 0};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::OUTFLOW, BC::REFLECTIVE, BC::REFLECTIVE});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

/*
 * Test if the particle is deleted at the front boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtFrontBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {5, 5, 2};
    std::array<double, 3> v1 = {0, 0, -4};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::OUTFLOW, BC::REFLECTIVE});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

/*
 * Test if the particle is deleted at the back boundary.
 */
TEST(OutflowBoundaryLC, DeletedAtBackBoundary) {
    std::vector<Particle> particles;

    std::array<double, 3> x1 = {5, 5, 8};
    std::array<double, 3> v1 = {0, 0, 4};

    auto particle = Particle(x1, v1, 1, 0);

    particles.push_back(particle);

    SimulationParams params("test_only.xml", "", 0.005, 1, 24, 30, SimulationParams::DirectSumType{}, std::nullopt, "none",
                            {"LennardJones"}, false, true);

    params.container_type = SimulationParams::LinkedCellsType(
        {10, 10, 10}, 5, {BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::REFLECTIVE, BC::OUTFLOW});

    Simulation simulation(particles, params);

    auto res = simulation.runSimulation();

    EXPECT_EQ(res.resulting_particles.size(), 0);
}

#include <gtest/gtest.h>

#include "particles/spawners/soft_body_cuboid/SoftBodyCuboidSpawner.h"
#include "utils/ArrayUtils.h"

/*
 * Macro to check if a point is in a list of points.
 */
#define EXPECT_CONTAINS_POS_NEAR(list, point, tol)                                                                              \
    EXPECT_TRUE(std::find_if((list).begin(), (list).end(), [&](auto& x) { return ArrayUtils::L2Norm(x - (point)) < (tol); }) != \
                (list).end());

/*
 * Test if a SoftBodyCuboidSpawner spawns the correct number of particles.
 */
TEST(SoftBodyParticleSpawner, SpawnCorrectNumberOfParticles) {
    std::array<double, 3> lower_left_corner = {0, 0, 0};
    std::array<int, 3> grid_dimensions = {3, 7, 11};
    double grid_spacing = 1;
    double mass = 1;
    std::array<double, 3> initial_velocity = {0, 0, 0};
    int type = 0;
    SoftBodyCuboidSpawner spawner(lower_left_corner, grid_dimensions, grid_spacing, mass, initial_velocity, type);

    std::vector<Particle> particle_container;
    spawner.spawnParticles(particle_container);

    ASSERT_EQ(particle_container.size(), 3 * 7 * 11);
}

/*
 * Test if a SoftBodyCuboidSpawner spawns the particles at the correct positions.
 */
TEST(SoftBodyParticleSpawner, SpawnParticlesAtCorrectPositions) {
    std::array<double, 3> lower_left_corner = {0, 0, 0};
    std::array<int, 3> grid_dimensions = {2, 3, 4};
    double grid_spacing = 1;
    double mass = 1;
    std::array<double, 3> initial_velocity = {0, 0, 0};
    int type = 0;
    SoftBodyCuboidSpawner spawner(lower_left_corner, grid_dimensions, grid_spacing, mass, initial_velocity, type);

    std::vector<Particle> particle_container;
    spawner.spawnParticles(particle_container);

    auto expected_positions =
        std::vector<std::array<double, 3>>({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {0, 2, 0}, {1, 2, 0}, {0, 0, 1}, {1, 0, 1},
                                            {0, 1, 1}, {1, 1, 1}, {0, 2, 1}, {1, 2, 1}, {0, 0, 2}, {1, 0, 2}, {0, 1, 2}, {1, 1, 2},
                                            {0, 2, 2}, {1, 2, 2}, {0, 0, 3}, {1, 0, 3}, {0, 1, 3}, {1, 1, 3}, {0, 2, 3}, {1, 2, 3}});

    for (const auto& i : particle_container) {
        // check if the position of the particle is inside the expected positions
        EXPECT_CONTAINS_POS_NEAR(expected_positions, i.getX(), 1e-10)
    }
}

/*
 * Test if a SoftBodyCuboidSpawner returns a good estimate of the actual number of particles.
 */
TEST(SoftBodyParticleSpawner, EstimateNumberOfParticles) {
    std::array<double, 3> lower_left = {0, 0, 0};
    double grid_spacing = 1;
    double mass = 1;
    std::array<double, 3> initial_velocity = {0, 0, 0};
    int type = 0;

    SoftBodyCuboidSpawner spawner2(lower_left, {2, 3, 4}, grid_spacing, mass, initial_velocity, type);
    std::vector<Particle> particle_container2;
    spawner2.spawnParticles(particle_container2);
    EXPECT_EQ(spawner2.getEstimatedNumberOfParticles(), particle_container2.size());

    SoftBodyCuboidSpawner spawner16(lower_left, {4, 5, 6}, grid_spacing, mass, initial_velocity, type);
    std::vector<Particle> particle_container16;
    spawner16.spawnParticles(particle_container16);
    EXPECT_EQ(spawner16.getEstimatedNumberOfParticles(), particle_container16.size());
}

/*
 * Test if a SoftBodyCuboidSpawner spawns the particles with the correct links within the membrane.
 */
TEST(SoftBodyParticleSpawner, CheckLinksWithinSoftBody) {
    std::array<double, 3> lower_left = {0, 0, 0};
    double grid_spacing = 1;
    double mass = 1;
    std::array<double, 3> initial_velocity = {0, 0, 0};
    int type = 0;

    std::vector<Particle> particles;
    particles.push_back(Particle({0, 0, 0}, {0, 0, 0}, mass, type, 0, 0));
    // Add one particle first to check for offset errors

    SoftBodyCuboidSpawner spawner(lower_left, {4, 5, 6}, grid_spacing, mass, initial_velocity, type);
    spawner.spawnParticles(particles);
    EXPECT_EQ(spawner.getEstimatedNumberOfParticles(), particles.size() - 1);

    std::vector<std::tuple<int, double, double>> expected_links_1 = {{&(particles[2]) - &(particles[1]), 1.0, 300},
                                                                     {&(particles[7]) - &(particles[1]), 1.0, 300},
                                                                     {&(particles[8]) - &(particles[1]), std::sqrt(2.0), 300},
                                                                     {&(particles[31]) - &(particles[1]), 1.0, 300},
                                                                     {&(particles[32]) - &(particles[1]), std::sqrt(2.0), 300},
                                                                     {&(particles[37]) - &(particles[1]), std::sqrt(2.0), 300},
                                                                     {&(particles[38]) - &(particles[1]), std::sqrt(3.0), 300}};

    EXPECT_EQ(particles[1].getConnectedParticles().size(), expected_links_1.size());

    for (size_t i = 0; i < particles[1].getConnectedParticles().size(); i++) {
        EXPECT_EQ(std::get<0>(particles[1].getConnectedParticles()[i]), std::get<0>(expected_links_1[i]));
        std::cout << (&(particles[1]) + std::get<0>(particles[1].getConnectedParticles()[i]))->getX() << std::endl;
        EXPECT_EQ(std::get<1>(particles[1].getConnectedParticles()[i]), std::get<1>(expected_links_1[i]));
        EXPECT_EQ(std::get<2>(particles[1].getConnectedParticles()[i]), std::get<2>(expected_links_1[i]));
    }

    std::vector<std::tuple<int, double, double>> expected_links_45 = {
        {&(particles[8]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[9]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[10]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[14]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[15]) - &(particles[45]), 1.0, 300},
        {&(particles[16]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[20]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[21]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[22]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[38]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[39]) - &(particles[45]), 1.0, 300},
        {&(particles[40]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[44]) - &(particles[45]), 1.0, 300},
        {&(particles[46]) - &(particles[45]), 1.0, 300},
        {&(particles[50]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[51]) - &(particles[45]), 1.0, 300},
        {&(particles[52]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[68]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[69]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[70]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[74]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[75]) - &(particles[45]), 1.0, 300},
        {&(particles[76]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[80]) - &(particles[45]), std::sqrt(3.0), 300},
        {&(particles[81]) - &(particles[45]), std::sqrt(2.0), 300},
        {&(particles[82]) - &(particles[45]), std::sqrt(3.0), 300},
    };

    EXPECT_EQ(particles[45].getConnectedParticles().size(), expected_links_45.size());
    for (size_t i = 0; i < particles[45].getConnectedParticles().size(); i++) {
        EXPECT_EQ(std::get<0>(particles[45].getConnectedParticles()[i]), std::get<0>(expected_links_45[i]));
        std::cout << (&(particles[45]) + std::get<0>(particles[45].getConnectedParticles()[i]))->getX() << std::endl;
        EXPECT_EQ(std::get<1>(particles[45].getConnectedParticles()[i]), std::get<1>(expected_links_45[i]));
        EXPECT_EQ(std::get<2>(particles[45].getConnectedParticles()[i]), std::get<2>(expected_links_45[i]));
    }
}

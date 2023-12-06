#include <gtest/gtest.h>

#include "data/FileLoader.h"
#include "io/input/chkpt/ChkptPointFileReader.h"
#include "particles/containers/ParticleContainer.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "utils/ArrayUtils.h"

#define EXPECT_CONTAINS_POS_NEAR(list, point, tol) \
    EXPECT_TRUE(std::find_if(list.begin(), list.end(), [&](auto& x) { return ArrayUtils::L2Norm(x - point) < tol; }) != list.end());

/*
 * Test if a CubFileReader reads the correct data out of the files.
 */
TEST(ChkptPointFileReader, CorrectReadingOfParticles) {
    std::unique_ptr<ParticleContainer> particle_container = std::make_unique<DirectSumContainer>();
    ChkptPointFileReader chkpt_reader;
    chkpt_reader.readFile(FileLoader::get_input_file_path("ChktpExample.chkpt"), particle_container);

    EXPECT_EQ(particle_container->size(), 2);

    auto expected_particle1 = Particle({1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, 13, 14);
    auto expected_particle2 = Particle({15, 16, 17}, {18, 19, 20}, {21, 22, 23}, {24, 25, 26}, 27, 28);

    std::vector<Particle> expected_particles = {expected_particle1, expected_particle2};

    for (int i = 0; i < particle_container->size(); i++) {
        auto& particle = (*particle_container)[i];
        auto& expected_particle = expected_particles[i];

        EXPECT_EQ(particle.getX(), expected_particle.getX());
        EXPECT_EQ(particle.getV(), expected_particle.getV());
        EXPECT_EQ(particle.getF(), expected_particle.getF());
        EXPECT_EQ(particle.getOldF(), expected_particle.getOldF());
        EXPECT_EQ(particle.getM(), expected_particle.getM());
        EXPECT_EQ(particle.getType(), expected_particle.getType());
    }
}
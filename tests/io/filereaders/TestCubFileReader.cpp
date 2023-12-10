#include <gtest/gtest.h>

#include "data/FileLoader.h"
#include "io/input/custom_formats/cub/CubFileReader.h"

#define EXPECT_CONTAINS_POS_NEAR(list, point, tol)                                                                              \
    EXPECT_TRUE(std::find_if((list).begin(), (list).end(), [&](auto& x) { return ArrayUtils::L2Norm(x - (point)) < (tol); }) != \
                (list).end());

/*
 * Test if a CubFileReader reads the correct data out of the files.
 */
TEST(CubFileReader, CorrectReadingOfParticles) {
    CubFileReader cub_file_reader;

    auto [particles, params] = cub_file_reader.readFile(FileLoader::get_input_file_path("CubExample.cub"));

    EXPECT_EQ(particles.size(), 4 * 7 * 3 + 2 * 2 * 1);

    EXPECT_NEAR((particles)[0].getM(), 3.14, 1e-13);
    EXPECT_EQ((particles)[0].getType(), 42);

    EXPECT_NEAR((particles)[particles.size() - 1].getM(), 6.0, 1e-13);
    EXPECT_EQ((particles)[particles.size() - 1].getType(), 112);
}
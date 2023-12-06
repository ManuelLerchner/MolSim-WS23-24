#include <gtest/gtest.h>

#include <optional>

#include "data/FileLoader.h"
#include "io/input/xml/XMLFileReader.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "utils/ArrayUtils.h"

#define EXPECT_CONTAINS_POS_NEAR(list, point, tol) \
    EXPECT_TRUE(std::find_if(list.begin(), list.end(), [&](auto& x) { return ArrayUtils::L2Norm(x - point) < tol; }) != list.end());

TEST(XMLFileReader, CorrectParticleContainer) {
    XMLFileReader file_reader;

    auto [particles, params] = file_reader.readFile(FileLoader::get_input_file_path("test_collision.xml"));

    auto conf = *params;

    double err = 1e-13;
    EXPECT_EQ(conf.video_length, 10);
    EXPECT_EQ(conf.fps, 24);
    EXPECT_NEAR(conf.end_time, 100, err);
    EXPECT_NEAR(conf.delta_t, 0.0014, err);

    EXPECT_EQ(particles.size(), 10 * 2 * 4 + 3 * 3 * 3 + 1);

    EXPECT_EQ(conf.output_format, FileOutputHandler::OutputFormat::VTK);
    EXPECT_EQ(conf.container_type.index(), 0);

    for (int i = 0; i < 80; i++) {
        EXPECT_NEAR((particles)[i].getM(), 1, err);
    }
    for (int i = 80; i < 107; i++) {
        EXPECT_NEAR((particles)[i].getM(), 1.5, err);
        EXPECT_EQ(2, (particles)[i].getType());
    }
    EXPECT_EQ(10, (particles)[107].getType());
    EXPECT_NEAR((particles)[107].getM(), 100, err);

    EXPECT_NEAR((particles)[0].getX()[0], 0, err);
    EXPECT_NEAR((particles)[0].getX()[1], 0, err);
    EXPECT_NEAR((particles)[0].getX()[2], 0, err);

    EXPECT_NEAR((particles)[80].getX()[0], 100, err);
    EXPECT_NEAR((particles)[80].getX()[1], 20, err);
    EXPECT_NEAR((particles)[80].getX()[2], 20, err);

    EXPECT_NEAR((particles)[107].getX()[0], 20, err);
    EXPECT_NEAR((particles)[107].getX()[1], 100, err);
    EXPECT_NEAR((particles)[107].getX()[2], 100, err);
}
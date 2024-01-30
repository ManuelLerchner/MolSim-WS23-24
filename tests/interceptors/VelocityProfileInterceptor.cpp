#include "simulation/interceptors/velocity_profile/VelocityProfileInterceptor.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <memory>

#include "simulation/SimulationUtils.h"

TEST(VelocityProfileInterceptor, TestBasicMeasurment) {
    Logger::logger->set_level(spdlog::level::warn);

    std::vector<Particle> particles = {
        Particle({0, 0, 0}, {1, 2, 3}, 1, 0),
        Particle({1, 0, 0}, {1, 2, 3}, 1, 0),
        Particle({0, 1, 0}, {1, 2, 3}, 1, 0),
        Particle({1, 1, 0}, {1, 2, 3}, 1, 0),
    };

    SimulationParams params_lc = TEST_DEFAULT_PARAMS_LENNARD_JONES;

    Simulation simulation_lc(particles, params_lc);

    std::pair<std::array<double, 3>, std::array<double, 3>> box =
        std::make_pair(std::array<double, 3>{-0.5, -0.5, -0.5}, std::array<double, 3>{1.5, 1.5, 1.5});

    VelocityProfileInterceptor interceptor(box, 2, 1);

    interceptor.onSimulationStart(simulation_lc);

    interceptor(1, simulation_lc);

    // check if csv file was created

    std::string csv_file_name_x = "statistics/velocity_profile_x_axis.csv";
    std::filesystem::path csv_file_path_x = params_lc.output_dir_path / csv_file_name_x;

    std::string csv_file_name_y = "statistics/velocity_profile_y_axis.csv";
    std::filesystem::path csv_file_path_y = params_lc.output_dir_path / csv_file_name_y;

    std::string csv_file_name_z = "statistics/velocity_profile_z_axis.csv";
    std::filesystem::path csv_file_path_z = params_lc.output_dir_path / csv_file_name_z;

    ASSERT_TRUE(std::filesystem::exists(csv_file_path_x));
    ASSERT_TRUE(std::filesystem::exists(csv_file_path_y));
    ASSERT_TRUE(std::filesystem::exists(csv_file_path_z));

    std::ifstream csv_file_x(csv_file_path_x);
    std::ifstream csv_file_y(csv_file_path_y);
    std::ifstream csv_file_z(csv_file_path_z);

    // check x. Values are trivial since every bin has the exact same particle velocities in it

    std::string linex;
    std::getline(csv_file_x, linex);

    ASSERT_EQ(linex, "\"iteration\";\"bin_index (w= 1.000000)\";\"avg_velocity_x\";\"avg_velocity_y\";\"avg_velocity_z\"");
    std::getline(csv_file_x, linex);

    ASSERT_EQ(linex, "0;0;1;2;3");
    std::getline(csv_file_x, linex);

    ASSERT_EQ(linex, "0;1;1;2;3");
    std::getline(csv_file_x, linex);

    ASSERT_EQ(linex, "1;0;1;2;3");
    std::getline(csv_file_x, linex);

    ASSERT_EQ(linex, "1;1;1;2;3");
    std::getline(csv_file_x, linex);

    ASSERT_TRUE(csv_file_x.eof());

    // check y. Values are the same as in x
    std::string liney;
    std::getline(csv_file_y, liney);

    ASSERT_EQ(liney, "\"iteration\";\"bin_index (w= 1.000000)\";\"avg_velocity_x\";\"avg_velocity_y\";\"avg_velocity_z\"");
    std::getline(csv_file_y, liney);

    ASSERT_EQ(liney, "0;0;1;2;3");
    std::getline(csv_file_y, liney);

    ASSERT_EQ(liney, "0;1;1;2;3");
    std::getline(csv_file_y, liney);

    ASSERT_EQ(liney, "1;0;1;2;3");
    std::getline(csv_file_y, liney);

    ASSERT_EQ(liney, "1;1;1;2;3");
    std::getline(csv_file_y, liney);

    ASSERT_TRUE(csv_file_y.eof());

    // check z. Values are the same as in x
    std::string linez;
    std::getline(csv_file_z, linez);

    ASSERT_EQ(linez, "\"iteration\";\"bin_index (w= 1.000000)\";\"avg_velocity_x\";\"avg_velocity_y\";\"avg_velocity_z\"");
    std::getline(csv_file_z, linez);

    ASSERT_EQ(linez, "0;0;1;2;3");
    std::getline(csv_file_z, linez);

    ASSERT_EQ(linez, "1;0;1;2;3");
    std::getline(csv_file_z, linez);

    ASSERT_TRUE(csv_file_z.eof());
}
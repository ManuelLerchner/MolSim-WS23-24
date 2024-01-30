#include "simulation/interceptors/radial_distribution_function/RadialDistributionFunctionInterceptor.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <memory>

#include "simulation/SimulationUtils.h"

TEST(RadialDistributionFunction, IsCorrectForSmallGrid_OneBin) {
    Logger::logger->set_level(spdlog::level::warn);

    std::vector<Particle> particles = {
        Particle({0, 0, 0}, {0, 0, 0}, 1, 0),
        Particle({1, 0, 0}, {0, 0, 0}, 1, 0),
        Particle({0, 1, 0}, {0, 0, 0}, 1, 0),
        Particle({1, 1, 0}, {0, 0, 0}, 1, 0),
    };

    SimulationParams params_lc = TEST_DEFAULT_PARAMS_LENNARD_JONES;

    Simulation simulation_lc(particles, params_lc);

    RadialDistributionFunctionInterceptor interceptor(2, 1);

    interceptor.onSimulationStart(simulation_lc);

    interceptor(1, simulation_lc);

    // check if csv file was created

    std::string csv_file_name = "statistics/radial_distribution_function.csv";
    std::filesystem::path csv_file_path = params_lc.output_dir_path / csv_file_name;

    ASSERT_TRUE(std::filesystem::exists(csv_file_path));

    std::ifstream csv_file(csv_file_path);

    std::string line;
    std::getline(csv_file, line);

    ASSERT_EQ(line, "\"iteration\";\"bin_index (w= 2.000000)\";\"samples\";\"local_density\"");

    std::getline(csv_file, line);

    // Hand calculated for the small example that all particles are in a grid
    ASSERT_EQ(line, "0;0;6;0.179049");

    std::getline(csv_file, line);

    ASSERT_EQ(line, "1;0;6;0.179049");

    std::getline(csv_file, line);

    ASSERT_TRUE(csv_file.eof());
}

TEST(RadialDistributionFunction, IsCorrectForSmallGrid_TwoBins) {
    Logger::logger->set_level(spdlog::level::warn);

    std::vector<Particle> particles = {
        Particle({0, 0, 0}, {0, 0, 0}, 1, 0),
        Particle({1, 0, 0}, {0, 0, 0}, 1, 0),
        Particle({0, 1, 0}, {0, 0, 0}, 1, 0),
        Particle({1, 1, 0}, {0, 0, 0}, 1, 0),
    };

    SimulationParams params_lc = TEST_DEFAULT_PARAMS_LENNARD_JONES;

    Simulation simulation_lc(particles, params_lc);

    RadialDistributionFunctionInterceptor interceptor(1.2, 1);

    interceptor.onSimulationStart(simulation_lc);

    interceptor(1, simulation_lc);

    // check if csv file was created

    std::string csv_file_name = "statistics/radial_distribution_function.csv";
    std::filesystem::path csv_file_path = params_lc.output_dir_path / csv_file_name;

    ASSERT_TRUE(std::filesystem::exists(csv_file_path));

    std::ifstream csv_file(csv_file_path);

    std::string line;
    std::getline(csv_file, line);

    ASSERT_EQ(line, "\"iteration\";\"bin_index (w= 1.200000)\";\"samples\";\"local_density\"");

    std::getline(csv_file, line);

    // Hand calculated for the small example that all particles are in a grid
    ASSERT_EQ(line, "0;0;4;0.552621");

    std::getline(csv_file, line);

    ASSERT_EQ(line, "0;1;2;0.039473");

    std::getline(csv_file, line);

    // Particles did not move, so the result should be the same
    ASSERT_EQ(line, "1;0;4;0.552621");

    std::getline(csv_file, line);

    ASSERT_EQ(line, "1;1;2;0.039473");

    std::getline(csv_file, line);

    ASSERT_TRUE(csv_file.eof());
}
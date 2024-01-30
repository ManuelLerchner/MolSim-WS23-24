#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <memory>

#include "simulation/SimulationUtils.h"
#include "simulation/interceptors/diffusion_function/DiffusionFunctionInterceptor.h"

std::vector<Particle> createParticles1() {
    std::array<double, 3> x1 = {5.5, 4.8, 3.2};
    std::array<double, 3> v1 = {0.2, 0.1, 0};

    std::array<double, 3> x2 = {5.7, 5.2, 7.4};
    std::array<double, 3> v2 = {-0.1, 0.2, 0};

    std::array<double, 3> x3 = {4.2, 5.6, 5.8};
    std::array<double, 3> v3 = {0.1, -0.2, 0};

    std::array<double, 3> x4 = {6.3, 6.2, 4};
    std::array<double, 3> v4 = {0.1, 0.1, 0};

    return {Particle(x1, v1, 1, 0), Particle(x2, v2, 1, 0), Particle(x3, v3, 1, 0), Particle(x4, v4, 1, 0)};
}

TEST(DiffusionInterceptor, IsZeroForNonMovingParticles) {
    Logger::logger->set_level(spdlog::level::warn);

    auto particles = createParticles1();

    SimulationParams params_lc = TEST_DEFAULT_PARAMS_LENNARD_JONES;

    Simulation simulation_lc(particles, params_lc);

    DiffusionFunctionInterceptor interceptor(1);

    interceptor.onSimulationStart(simulation_lc);

    interceptor(1, simulation_lc);

    // check if csv file was created

    std::string csv_file_name = "statistics/diffusion_function.csv";
    std::filesystem::path csv_file_path = params_lc.output_dir_path / csv_file_name;

    ASSERT_TRUE(std::filesystem::exists(csv_file_path));

    std::ifstream csv_file(csv_file_path);

    std::string line;
    std::getline(csv_file, line);

    ASSERT_EQ(line, "\"iteration\";\"var(t)\"");
    std::getline(csv_file, line);

    ASSERT_EQ(line, "1;0");

    std::getline(csv_file, line);

    ASSERT_TRUE(csv_file.eof());
}

TEST(DiffusionInterceptor, CalculatesCorrectDiffusion) {
    Logger::logger->set_level(spdlog::level::warn);

    auto particles = createParticles1();

    SimulationParams params_lc = TEST_DEFAULT_PARAMS_LENNARD_JONES;

    Simulation simulation_lc(particles, params_lc);

    DiffusionFunctionInterceptor interceptor(1);

    interceptor.onSimulationStart(simulation_lc);

    for (auto& p : particles) {
        p.setX({p.getX()[0] + 1, p.getX()[1] + 1, p.getX()[2] + 1});
    }

    Simulation simulation_lc_new(particles, params_lc);

    interceptor(1, simulation_lc_new);

    // check if csv file was created

    std::string csv_file_name = "statistics/diffusion_function.csv";
    std::filesystem::path csv_file_path = params_lc.output_dir_path / csv_file_name;

    ASSERT_TRUE(std::filesystem::exists(csv_file_path));

    std::ifstream csv_file(csv_file_path);

    std::string line;
    std::getline(csv_file, line);

    ASSERT_EQ(line, "\"iteration\";\"var(t)\"");
    std::getline(csv_file, line);

    // Every particle moved by sqrt(3) therfore the variance is 3
    ASSERT_EQ(line, "1;3");

    std::getline(csv_file, line);

    ASSERT_TRUE(csv_file.eof());
}
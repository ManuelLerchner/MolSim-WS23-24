#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>

#include "data/FileLoader.h"
#include "io/input/FileInputHandler.h"
#include "simulation/Simulation.h"
#include "simulation/SimulationUtils.h"
#include "utils/ArrayUtils.h"

auto load_all_input_files() {
    std::vector<std::string> input_files;
    auto supported_extensions = FileInputHandler::get_supported_input_file_extensions();

    for (const auto& entry : std::filesystem::recursive_directory_iterator(FileLoader::get_test_data_dir() + "/input")) {
        // check for valid extension

        if (supported_extensions.find(entry.path().extension()) == supported_extensions.end()) {
            continue;
        }

        input_files.push_back(entry.path());
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(FileLoader::get_test_data_dir() + "/../../input")) {
        // check for valid extension

        if (supported_extensions.find(entry.path().extension()) == supported_extensions.end()) {
            continue;
        }

        input_files.push_back(entry.path());
    }
    return input_files;
}

/*
 * Test that all input files can be read and simulated
 */
TEST(SimulationRunner, EnsureBackwardsCompatibilityForAllInputFiles) {
    Logger::logger->set_level(spdlog::level::off);

    std::set<std::string> tested_extensions = {};

    for (const auto& input_file : load_all_input_files()) {
        std::cout << "Testing input file: " << input_file << std::endl;

        tested_extensions.insert(input_file.substr(input_file.find_last_of('.')));

        // Create pointer for particle container

        // Parse input file
        auto [particles, _] = FileInputHandler::readFile(input_file);

        EXPECT_GT(particles.size(), 0);

        // Create all force sources acting on the particles

        SimulationParams params = TEST_DEFAULT_PARAMS_LENNARD_JONES;

        params.end_time = 0.1;
        params.delta_t = 0.01;
        params.output_format = FileOutputHandler::OutputFormat::NONE;

        // Initialize simulation
        Simulation simulation{particles, params};

        // Run simulation
        auto res = simulation.runSimulation();

        EXPECT_GT(res.total_iterations, 0);
    }

    // Check that all supported extensions have actually been tested
    for (const auto& extension : FileInputHandler::get_supported_input_file_extensions()) {
        EXPECT_TRUE(tested_extensions.find(extension) != tested_extensions.end());
    }
}
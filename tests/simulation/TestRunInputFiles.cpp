#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <memory>

#include "data/FileLoader.h"
#include "io/input/FileInputHandler.h"
#include "particles/containers/ParticleContainer.h"
#include "physics/forces/ForceSource.h"
#include "physics/forces/LennardJonesForce.h"
#include "simulation/Simulation.h"
#include "simulation/SimulationUtils.h"
#include "utils/ArrayUtils.h"

auto load_all_input_files() {
    std::vector<std::string> input_files;

    std::set<std::string> found_extensions = {};

    for (const auto& entry : std::filesystem::recursive_directory_iterator(FileLoader::get_test_data_dir() + "/../../input")) {
        // check for valid extension
        auto supported_extensions = get_supported_input_file_extensions();

        if (supported_extensions.find(entry.path().extension()) == supported_extensions.end()) {
            continue;
        }

        input_files.push_back(entry.path());
        found_extensions.insert(entry.path().extension());
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(FileLoader::get_test_data_dir() + "/input")) {
        // check for valid extension
        auto supported_extensions = get_supported_input_file_extensions();

        if (supported_extensions.find(entry.path().extension()) == supported_extensions.end()) {
            continue;
        }

        input_files.push_back(entry.path());
        found_extensions.insert(entry.path().extension());
    }

    for (const auto& extension : get_supported_input_file_extensions()) {
        if (found_extensions.find(extension) == found_extensions.end()) {
            throw std::runtime_error("No input file found for extension " + extension);
        }
    }

    return input_files;
}

/*
 * Test that all input files can be read and simulated
 */
TEST(SimulationRunner, EnsureBackwardsCompatibilityForAllInputFiles) {
    Logger::logger->set_level(spdlog::level::warn);

    // Check that all supported extensions have actually been tested

    for (const auto& input_file : load_all_input_files()) {
        std::cout << "Testing input file: " << input_file << std::endl;

        // Parse input file
        auto [particles, file_config] = FileInputHandler::readFile(input_file, true, false);

        auto config = file_config.value_or(TEST_DEFAULT_PARAMS_LENNARD_JONES);

        config.end_time = 0.1;
        config.delta_t = 0.001;
        config.output_format = OutputFormat::NONE;

        // Initialize simulation
        Simulation simulation{particles, config};

        // Run simulation
        auto res = simulation.runSimulation();

        EXPECT_GT(res.total_iterations, 0);
    }
}
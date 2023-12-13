#include "Simulation.h"

#include <spdlog/fmt/chrono.h>

#include <chrono>
#include <filesystem>
#include <iostream>

#include "integration/VerletFunctor.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "utils/FormatTime.h"

void printProgress(const std::string& input_file_path, size_t percentage, size_t iteration, size_t expected_iterations,
                   int estimated_remaining_seconds, bool finished = false) {
    auto file_name = std::filesystem::path(input_file_path).stem().string();

    std::string progress = fmt::format("[{}{}] Iteration: {}/{}, {:>3}%, ETA: {} - [{}]", ansi_blue_bold + std::string(percentage, '#'),
                                       std::string(100 - percentage, ' ') + ansi_end, iteration, expected_iterations, percentage,
                                       format_seconds_eta(estimated_remaining_seconds), file_name);

    std::cout << progress << "\r" << (finished ? "\n" : "") << std::flush;
}

Simulation::Simulation(const std::vector<Particle>& initial_particles, const SimulationParams& params, IntegrationMethod integration_method)
    : file_output_handler(FileOutputHandler(params)), params(params) {
    // Create particle container
    if (std::holds_alternative<SimulationParams::LinkedCellsType>(params.container_type)) {
        auto linked_cells = std::get<SimulationParams::LinkedCellsType>(params.container_type);
        particles =
            std::make_unique<LinkedCellsContainer>(linked_cells.domain_size, linked_cells.cutoff_radius, linked_cells.boundary_conditions);
    } else if (std::holds_alternative<SimulationParams::DirectSumType>(params.container_type)) {
        particles = std::make_unique<DirectSumContainer>();
    } else {
        throw std::runtime_error("Unknown container type");
    }

    // Add particles to container
    particles->reserve(initial_particles.size());
    for (auto& particle : initial_particles) {
        particles->addParticle(particle);
    }

    switch (integration_method) {
        case IntegrationMethod::VERLET:
            integration_functor = std::make_unique<VerletFunctor>();
            break;
        default:
            Logger::logger->error("Integration method not implemented.");
            exit(-1);
    }
}

SimulationOverview Simulation::runSimulation() {
    size_t iteration = 0;
    double simulation_time = 0;

    const size_t expected_iterations = std::floor(params.end_time / params.delta_t);

    bool no_output = params.fps == 0 || params.video_length == 0;

    const size_t save_every_nth_iteration =
        no_output ? expected_iterations / 100 : std::max(expected_iterations / (params.fps * params.video_length), 1ul);

    Logger::logger->info("Simulation started...");

    // Calculate initial forces
    particles->prepareForceCalculation();
    particles->applySimpleForces(params.simple_forces);
    particles->applyPairwiseForces(params.pairwise_forces);

    // keep track of time for progress high precision
    auto start_time = std::chrono::high_resolution_clock::now();

    auto t_prev = start_time;

    while (simulation_time < params.end_time) {
        if (iteration % save_every_nth_iteration == 0) {
            // calculate time since last write
            auto t_now = std::chrono::high_resolution_clock::now();
            const double seconds_since_last_write = std::chrono::duration<double>(t_now - t_prev).count();
            t_prev = t_now;

            // calculate estimated remaining time
            const int estimated_remaining_seconds =
                (iteration != 0) ? std::floor(seconds_since_last_write * static_cast<double>(expected_iterations - iteration) /
                                              static_cast<double>(save_every_nth_iteration))
                                 : -1;

            const size_t percentage = 100 * iteration / expected_iterations;

            printProgress(params.input_file_path, percentage, iteration, expected_iterations, estimated_remaining_seconds);

            if (!no_output) {
                file_output_handler.writeFile(iteration, particles);
            }
        }

        integration_functor->step(particles, params.simple_forces, params.pairwise_forces, params.delta_t);

        if (params.thermostat.has_value() && iteration != 0 && iteration % params.thermostat->getApplicationInterval() == 0) {
            params.thermostat.value().scaleTemperature(particles);
        }

        iteration++;
        simulation_time += params.delta_t;
    }

    printProgress(params.input_file_path, 100, expected_iterations, expected_iterations, 0, true);

    Logger::logger->info("Simulation finished.");

    auto total_simulation_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();

    return SimulationOverview{params,
                              static_cast<double>(total_simulation_time_ms) / 1000.0,
                              static_cast<double>(total_simulation_time_ms) / static_cast<double>(iteration),
                              static_cast<size_t>(iteration - 1),
                              expected_iterations / save_every_nth_iteration + 1,
                              std::vector<Particle>(particles->begin(), particles->end())};
}

SimulationOverview Simulation::runSimulationPerfTest() {
    const size_t initial_particle_count = particles->size();

    double simulation_time = 0;
    size_t iteration = 0;

    // Calculate initial forces
    particles->prepareForceCalculation();
    particles->applySimpleForces(params.simple_forces);
    particles->applyPairwiseForces(params.pairwise_forces);

    // keep track of time for progress high precision
    auto start_time = std::chrono::high_resolution_clock::now();

    while (simulation_time < params.end_time) {
        integration_functor->step(particles, params.simple_forces, params.pairwise_forces, params.delta_t);

        if (params.thermostat && iteration != 0 && iteration % params.thermostat->getApplicationInterval() == 0) {
            (*params.thermostat).scaleTemperature(particles);
        }

        simulation_time += params.delta_t;
        iteration++;
    }

    auto total_simulation_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();

    SimulationOverview overview{params,
                                static_cast<double>(total_simulation_time) / 1000.0,
                                static_cast<double>(total_simulation_time) / static_cast<double>(iteration),
                                static_cast<size_t>(iteration - 1),
                                0,
                                std::vector<Particle>(particles->begin(), particles->end())};

    savePerformanceTest(overview, params, initial_particle_count);

    return overview;
}

void Simulation::savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params, size_t num_particles) {
    if (!std::filesystem::exists(params.output_dir_path)) {
        std::filesystem::create_directories(params.output_dir_path);
    }

    std::ofstream csv_file;

    if (!std::filesystem::exists(params.output_dir_path + "/performance_test.csv")) {
        csv_file.open(params.output_dir_path + "/performance_test.csv");
        // Write the Headers to the file
        csv_file << "datetime,num_particles,particle_container,delta_t,total_time[s],time_per_iteration[ms],total_iterations\n";
    } else {
        csv_file.open(params.output_dir_path + "/performance_test.csv", std::ios_base::app);
    }

    std::string container_type_string;
    if (std::holds_alternative<SimulationParams::DirectSumType>(params.container_type)) {
        container_type_string = std::string(std::get<SimulationParams::DirectSumType>(params.container_type));
    } else if (std::holds_alternative<SimulationParams::LinkedCellsType>(params.container_type)) {
        container_type_string = std::string(std::get<SimulationParams::LinkedCellsType>(params.container_type));
    } else {
        Logger::logger->error("Invalid container type when saving performance test");
        exit(-1);
    }

    // write the results to the file
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto formatted_time = fmt::format("{:%d.%m.%Y-%H:%M:%S}", fmt::localtime(now));
    csv_file << formatted_time << "," << num_particles << "," << container_type_string << "," << params.delta_t << ","
             << overview.total_time_seconds << "," << overview.average_time_per_iteration_millis << "," << overview.total_iterations
             << "\n";

    // close the file
    csv_file.close();
}

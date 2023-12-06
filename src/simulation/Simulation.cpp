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

Simulation::Simulation(const std::vector<Particle>& initial_particles, const std::vector<std::unique_ptr<ForceSource>>& forces,
                       const SimulationParams& simulation_params, IntegrationMethod integration_method)
    : delta_t(simulation_params.delta_t),
      simulation_end_time(simulation_params.end_time),
      file_output_handler(FileOutputHandler(simulation_params.output_format, simulation_params.output_dir_path)),
      fps(simulation_params.fps),
      video_length(simulation_params.video_length),
      simulation_params(simulation_params),
      forces(forces) {
    // Create particle container
    if (std::holds_alternative<SimulationParams::LinkedCellsType>(simulation_params.container_type)) {
        auto linked_cells = std::get<SimulationParams::LinkedCellsType>(simulation_params.container_type);
        particles =
            std::make_unique<LinkedCellsContainer>(linked_cells.domain_size, linked_cells.cutoff_radius, linked_cells.boundary_conditions);
    } else if (std::holds_alternative<SimulationParams::DirectSumType>(simulation_params.container_type)) {
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
            exit(1);
    }
}

SimulationOverview Simulation::runSimulation() {
    int iteration = 0;
    double simulation_time = 0;

    const size_t expected_iterations = simulation_end_time / delta_t;
    const size_t fill_width = log10(expected_iterations) + 1;

    bool no_output = fps == 0 || video_length == 0;

    const size_t save_every_nth_iteration =
        no_output ? std::numeric_limits<size_t>::max() : std::max(expected_iterations / (fps * video_length), 1ul);

    Logger::logger->info("Simulation started...");

    // Calculate initial forces
    particles->applyPairwiseForces(forces);

    // keep track of time for progress high precision
    auto start_time = std::chrono::high_resolution_clock::now();
    auto t_now = start_time;
    auto t_prev = start_time;

    while (simulation_time < simulation_end_time) {
        if (!no_output && iteration % save_every_nth_iteration == 0) {
            // calculate time since last write
            t_now = std::chrono::high_resolution_clock::now();
            const double seconds_since_last_write = std::chrono::duration<double>(t_now - t_prev).count();
            t_prev = t_now;

            // calculate estimated remaining time
            const size_t estimated_remaining_seconds =
                (expected_iterations - iteration) * seconds_since_last_write / save_every_nth_iteration;

            const size_t percentage = 100 * iteration / expected_iterations;

            Logger::logger->info("Iteration {:>{}}/{} finished   {:>3}% (ETA: {})", iteration, fill_width, expected_iterations, percentage,
                                 format_seconds_eta(estimated_remaining_seconds));

            // write output
            file_output_handler.writeFile(iteration, particles);
        }

        integration_functor->step(particles, forces, delta_t);

        iteration++;
        simulation_time += delta_t;
    }

    // write final output
    file_output_handler.writeFile(iteration, particles);

    Logger::logger->info("Simulation finished.");

    auto total_simulation_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();

    return SimulationOverview{total_simulation_time / 1000.0, total_simulation_time / static_cast<double>(iteration - 1),
                              static_cast<size_t>(iteration - 1), expected_iterations / save_every_nth_iteration,
                              std::vector<Particle>(particles->begin(), particles->end())};
}

SimulationOverview Simulation::runSimulationPerfTest() {
    const size_t initial_particle_count = particles->size();

    double simulation_time = 0;
    size_t iteration = 0;

    // Calculate initial forces
    particles->applyPairwiseForces(forces);

    // keep track of time for progress high precision
    auto start_time = std::chrono::high_resolution_clock::now();

    while (simulation_time < simulation_end_time) {
        integration_functor->step(particles, forces, delta_t);

        simulation_time += delta_t;
        iteration++;
    }

    auto total_simulation_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();

    SimulationOverview overview{total_simulation_time / 1000.0, total_simulation_time / static_cast<double>(iteration),
                                static_cast<size_t>(iteration - 1), 0, std::vector<Particle>(particles->begin(), particles->end())};

    savePerformanceTest(overview, simulation_params, initial_particle_count);

    return overview;
}

void Simulation::savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params, size_t num_particles) const {
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
        container_type_string = std::get<SimulationParams::DirectSumType>(params.container_type);
    } else if (std::holds_alternative<SimulationParams::LinkedCellsType>(params.container_type)) {
        container_type_string = std::get<SimulationParams::LinkedCellsType>(params.container_type);
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

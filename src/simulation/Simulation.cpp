#include "Simulation.h"

#include <spdlog/fmt/chrono.h>

#include <chrono>
#include <filesystem>
#include <iostream>

#include "integration/IntegrationMethods.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "simulation/interceptors/SimulationInterceptor.h"
#include "simulation/interceptors/progress_bar/ProgressBarInterceptor.h"
#include "simulation/interceptors/save_file/SaveFileInterceptor.h"
#include "simulation/interceptors/thermostat/ThermostatInterceptor.h"

Simulation::Simulation(const std::vector<Particle>& initial_particles, const SimulationParams& params, IntegrationMethod integration_method)
    : params(params), integration_functor(get_integration_functor(integration_method)) {
    // Create particle container
    if (std::holds_alternative<SimulationParams::LinkedCellsType>(params.container_type)) {
        auto lc_type = std::get<SimulationParams::LinkedCellsType>(params.container_type);
        particle_container =
            std::make_unique<LinkedCellsContainer>(lc_type.domain_size, lc_type.cutoff_radius, lc_type.boundary_conditions);
    } else if (std::holds_alternative<SimulationParams::DirectSumType>(params.container_type)) {
        particle_container = std::make_unique<DirectSumContainer>();
    } else {
        throw std::runtime_error("Unknown container type");
    }

    // Add particles to container
    particle_container->reserve(initial_particles.size());
    for (auto& particle : initial_particles) {
        particle_container->addParticle(particle);
    }

    // Add interceptors to the simulation to allow for runtime monitoring
    if (!params.performance_test) {
        interceptors.push_back(std::make_unique<ProgressBarInterceptor>(*this));
    }

    if (params.fps > 0 && params.video_length > 0 && !params.performance_test) {
        interceptors.push_back(std::make_unique<SaveFileInterceptor>(*this));
    }

    if (params.thermostat) {
        interceptors.push_back(std::make_unique<ThermostatInterceptor>(*this));
    }
}

Simulation::~Simulation() = default;

SimulationOverview Simulation::runSimulation() {
    size_t iteration = 0;
    double simulated_time = 0;

    // Calculate initial forces
    particle_container->prepareForceCalculation();
    particle_container->applySimpleForces(params.simple_forces);
    particle_container->applyPairwiseForces(params.pairwise_forces);

    Logger::logger->info("Simulation started...");

    for (auto& interceptor : interceptors) {
        (*interceptor).onSimulationStart();
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    while (simulated_time < params.end_time) {
        integration_functor->step(particle_container, params.simple_forces, params.pairwise_forces, params.delta_t);

        iteration++;
        simulated_time += params.delta_t;

        for (auto& interceptor : interceptors) {
            (*interceptor).notify(iteration);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    for (auto& interceptor : interceptors) {
        (*interceptor).onSimulationEnd(iteration);
    }

    Logger::logger->info("Simulation finished.");

    std::vector<std::string> interceptor_summaries;
    for (auto& interceptor : interceptors) {
        interceptor_summaries.push_back(std::string(*interceptor));
    }

    auto simulation_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    return SimulationOverview{params,
                              static_cast<double>(simulation_duration_ms) / 1000.0,
                              static_cast<double>(simulation_duration_ms) / static_cast<double>(iteration),
                              static_cast<size_t>(iteration),
                              interceptor_summaries,
                              std::vector<Particle>(particle_container->begin(), particle_container->end())};
}

void Simulation::savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params) {
    if (!std::filesystem::exists(params.output_dir_path)) {
        std::filesystem::create_directories(params.output_dir_path);
    }

    std::ofstream csv_file;

    if (!std::filesystem::exists(params.output_dir_path / "performance_test.csv")) {
        csv_file.open(params.output_dir_path / "performance_test.csv");
        // Write the Headers to the file
        csv_file << "datetime,num_particles,particle_container,delta_t,total_time[s],time_per_iteration[ms],total_iterations\n";
    } else {
        csv_file.open(params.output_dir_path / "performance_test.csv", std::ios_base::app);
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
    csv_file << formatted_time << "," << params.num_particles << "," << container_type_string << "," << params.delta_t << ","
             << overview.total_time_seconds << "," << overview.particle_updates_per_second << "," << overview.total_iterations << "\n";

    // close the file
    csv_file.close();
}

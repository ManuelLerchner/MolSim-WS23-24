#include "Simulation.h"

#include <spdlog/fmt/chrono.h>

#include <filesystem>
#include <iostream>
#include <tuple>

#include "integration/IntegrationMethods.h"
#include "io/csv/CSVWriter.h"
#include "io/logger/Logger.h"
#include "particles/containers/directsum/DirectSumContainer.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "simulation/interceptors/SimulationInterceptor.h"
#include "simulation/interceptors/particle_update_counter/ParticleUpdateCounterInterceptor.h"
#include "simulation/interceptors/progress_bar/ProgressBarInterceptor.h"
#include "simulation/interceptors/radial_distribution_function/RadialDistributionFunctionInterceptor.h"
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
        interceptors.insert({"progress_bar", std::make_unique<ProgressBarInterceptor>(*this)});
    }

    if (params.fps > 0 && params.video_length > 0 && !params.performance_test) {
        interceptors.insert({"save_file", std::make_unique<SaveFileInterceptor>(*this)});
    }

    interceptors.insert({"particle_update_counter", std::make_unique<ParticleUpdateCounterInterceptor>(*this)});

    if (params.thermostat) {
        interceptors.insert({"thermostat", std::make_unique<ThermostatInterceptor>(*this)});
    }

    interceptors.insert({"radial_distribution_function", std::make_unique<RadialDistributionFunctionInterceptor>(*this)});
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

    // Notify interceptors that the simulation is about to start
    for (auto& [_, interceptor] : interceptors) {
        (*interceptor).onSimulationStart();
    }

    while (simulated_time < params.end_time) {
        integration_functor->step(particle_container, params.simple_forces, params.pairwise_forces, params.delta_t);

        ++iteration;
        simulated_time += params.delta_t;

        // Notify interceptors of the current iteration
        for (auto& [_, interceptor] : interceptors) {
            (*interceptor).notify(iteration);
        }
    }

    // Notify interceptors that the simulation has ended
    for (auto& [_, interceptor] : interceptors) {
        (*interceptor).onSimulationEnd(iteration);
    }

    Logger::logger->info("Simulation finished.");

    std::vector<std::string> interceptor_summaries;
    for (auto& [_, interceptor] : interceptors) {
        interceptor_summaries.push_back(std::string(*interceptor));
    }

    auto particle_update_counter = dynamic_cast<ParticleUpdateCounterInterceptor&>(*interceptors["particle_update_counter"]);

    SimulationOverview overview{params,
                                static_cast<double>(particle_update_counter.getSimulationDurationMS()) / 1000.0,
                                particle_update_counter.getParticleUpdatesPerSecond(),
                                iteration,
                                interceptor_summaries,
                                std::vector<Particle>(particle_container->begin(), particle_container->end())};

    if (params.performance_test) {
        savePerformanceTest(overview, params);
    }

    return overview;
}

void Simulation::savePerformanceTest(const SimulationOverview& overview, const SimulationParams& params) {
    // write the results to the file
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto formatted_time = fmt::format("{:%d.%m.%Y-%H:%M:%S}", fmt::localtime(now));

    CSVWriter csv_writer(
        params.output_dir_path / ("performance_test_" + formatted_time + ".csv"),
        {"num_particles", "particle_container", "delta_t", "total_time[s]", "particle_updates_per_second[1/s]", "total_iterations"});

    std::string container_type_string = std::visit([](auto&& arg) { return std::string(arg); }, params.container_type);

    csv_writer.writeRow({params.num_particles, container_type_string, params.delta_t, overview.total_time_seconds,
                         overview.particle_updates_per_second, overview.total_iterations});
}

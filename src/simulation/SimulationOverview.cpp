#include "SimulationOverview.h"

#include <spdlog/fmt/chrono.h>

#include <algorithm>
#include <chrono>
#include <ctime>

#include "io/logger/Logger.h"
#include "io/output/csv/CSVWriter.h"
#include "simulation/SimulationParams.h"
#include "simulation/interceptors/particle_update_counter/ParticleUpdateCounterInterceptor.h"
#include "utils/FormatTime.h"

void SimulationOverview::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╔════════════════════════════════════════", indent);
    Logger::logger->info("{}╟┤{}Simulation overview: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Input file: {}", indent, params.input_file_path.string());
    Logger::logger->info("{}║  Output directory: {}", indent, params.output_dir_path.string());
    Logger::logger->info("{}║  Simulation time: {}", indent, format_seconds_total(total_time_seconds));
    Logger::logger->info("{}║  Number of iterations: {}", indent, total_iterations);
    Logger::logger->info("{}║  Number of particles left: {}", indent, resulting_particles.size());
    Logger::logger->info("{}╟┤{}Interceptor Logs: {}", indent, ansi_yellow_bold, ansi_end);

    if (interceptor_summaries.empty()) {
        Logger::logger->info("{}║   └No interceptors", indent);
    } else {
        for (auto& interceptor_summary : interceptor_summaries) {
            Logger::logger->info("{}║   ├{}", indent, interceptor_summary);
        }
    }

    Logger::logger->info("{}╚════════════════════════════════════════", indent);
}

void SimulationOverview::savePerformanceDataCSV() const { savePerformanceDataCSV(""); }

void SimulationOverview::savePerformanceDataCSV(const std::string& filename_prefix) const {
    // write the results to the file
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto formatted_time = fmt::format("{:%d.%m.%Y-%H:%M:%S}", fmt::localtime(now));

    CSVWriter csv_writer(
        params.output_dir_path / "statistics" /
            (filename_prefix + (filename_prefix.empty() ? "" : "_") + "performance_data_" + formatted_time + ".csv"),
        {"num_particles", "particle_container", "delta_t", "total_time[s]", "particle_updates_per_second[1/s]", "total_iterations"});

    // find ParticleUpdateCounterInterceptor
    auto particle_update_counter = std::find_if(params.interceptors.begin(), params.interceptors.end(), [](auto& interceptor) {
        return std::dynamic_pointer_cast<ParticleUpdateCounterInterceptor>(interceptor) != nullptr;
    });

    auto particle_updates_per_second =
        particle_update_counter != params.interceptors.end()
            ? std::to_string(
                  std::dynamic_pointer_cast<ParticleUpdateCounterInterceptor>(*particle_update_counter)->getParticleUpdatesPerSecond())
            : "N/A";

    std::string container_type_string = std::visit([](auto&& arg) { return std::string(arg); }, params.container_type);

    csv_writer.writeRow(
        {params.num_particles, container_type_string, params.delta_t, total_time_seconds, particle_updates_per_second, total_iterations});
}
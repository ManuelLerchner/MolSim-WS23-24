#include "SimulationOverview.h"

#include "io/logger/Logger.h"
#include "utils/FormatTime.h"

void SimulationOverview::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╔════════════════════════════════════════", indent);
    Logger::logger->info("{}╟┤{}Simulation overview: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Input file: {}", indent, simulation_params.input_file_path);
    Logger::logger->info("{}║  Output directory: {}", indent, simulation_params.output_dir_path);
    Logger::logger->info("{}║  Simulation time: {}", indent, format_seconds_total(total_time_seconds));
    Logger::logger->info("{}║  Number of iterations: {}", indent, total_iterations);
    Logger::logger->info("{}║  Average iteration time: {:.3f}ms", indent, average_time_per_iteration_millis);
    Logger::logger->info("{}║  Number of files written: {}", indent, files_written);
    Logger::logger->info("{}║  Number of particles left: {}", indent, resulting_particles.size());
    Logger::logger->info("{}╚════════════════════════════════════════", indent);
}
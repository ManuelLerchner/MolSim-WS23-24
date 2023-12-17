#include "ProgressBarInterceptor.h"

#include <filesystem>
#include <format>
#include <iostream>

#include "io/logger/Logger.h"
#include "utils/FormatTime.h"

void printProgress(const std::filesystem::path& input_file_path, size_t percentage, size_t iteration, size_t expected_iterations,
                   int estimated_remaining_seconds, bool finished = false) {
    auto file_name = std::filesystem::path(input_file_path).stem().string();

    std::string progress = fmt::format("[{}{}] Iteration: {}/{}, {:>3}%, ETA: {} - [{}]", ansi_blue_bold + std::string(percentage, '#'),
                                       std::string(100 - percentage, ' ') + ansi_end, iteration, expected_iterations, percentage,
                                       format_seconds_eta(estimated_remaining_seconds), file_name);

    std::cout << progress << "\r" << (finished ? "\n" : "") << std::flush;
}

ProgressBarInterceptor::ProgressBarInterceptor(Simulation& simulation) : SimulationInterceptor(simulation) {
    expected_iterations = std::floor(simulation.params.end_time / simulation.params.delta_t);

    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(expected_iterations / 100));
}

void ProgressBarInterceptor::onSimulationStart() {
    t_start = std::chrono::high_resolution_clock::now();
    t_prev = t_start;

    Logger::logger->info("Start time: {}", std::format("{:%A %Y-%m-%d %H:%M:%S}", t_start));
    Logger::logger->flush();

    printProgress(simulation.params.input_file_path, 0, 0, expected_iterations, -1);
}

void ProgressBarInterceptor::operator()(int iteration) {
    // calculate time since last write
    auto t_now = std::chrono::high_resolution_clock::now();
    const double seconds_since_last_write = std::chrono::duration<double>(t_now - t_prev).count();
    t_prev = t_now;

    // calculate estimated remaining time
    const int estimated_remaining_seconds = std::floor(seconds_since_last_write * static_cast<double>(expected_iterations - iteration) /
                                                       static_cast<double>(every_nth_iteration));

    const size_t percentage = 100 * iteration / expected_iterations;

    printProgress(simulation.params.input_file_path, percentage, iteration, expected_iterations, estimated_remaining_seconds);
}

void ProgressBarInterceptor::onSimulationEnd(int iteration) {
    printProgress(simulation.params.input_file_path, 100, expected_iterations, expected_iterations, 0, true);

    t_end = std::chrono::high_resolution_clock::now();

    Logger::logger->info("End time: {}", std::format("{:%A %Y-%m-%d %H:%M:%S}", t_end));
}

ProgressBarInterceptor::operator std::string() const { return "ProgressBarInterceptor"; }
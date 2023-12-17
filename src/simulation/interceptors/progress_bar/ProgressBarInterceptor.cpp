#include "ProgressBarInterceptor.h"

#include <spdlog/fmt/chrono.h>

#include <filesystem>
#include <iostream>

#include "io/logger/Logger.h"
#include "simulation/SimulationParams.h"
#include "utils/FormatTime.h"

void printProgress(const std::filesystem::path& input_file_path, size_t percentage, size_t iteration, size_t expected_iterations,
                   int estimated_remaining_seconds, bool finished = false) {
    auto file_name = std::filesystem::path(input_file_path).stem().string();

    std::string progress = fmt::format("[{}{}] Iteration: {}/{}, {:>3}%, ETA: {} - [{}]", ansi_blue_bold + std::string(percentage, '#'),
                                       std::string(100 - percentage, ' ') + ansi_end, iteration, expected_iterations, percentage,
                                       format_seconds_eta(estimated_remaining_seconds), file_name);

    std::cout << progress << "\r" << (finished ? "\n" : "") << std::flush;
}

void ProgressBarInterceptor::onSimulationStart() {
    t_start = std::chrono::high_resolution_clock::now();
    t_prev = t_start;

    std::time_t t_start_helper = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Logger::logger->info("Start time: {}", fmt::format("{:%A %Y-%m-%d %H:%M:%S}", fmt::localtime(t_start_helper)));
    Logger::logger->flush();

    expected_iterations = static_cast<size_t>(std::ceil(simulation->params.end_time / simulation->params.delta_t) + 1);

    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(expected_iterations / 100));

    printProgress(simulation->params.input_file_path, 0, 0, expected_iterations, -1);
}

void ProgressBarInterceptor::operator()(size_t iteration) {
    // calculate time since last write
    auto t_now = std::chrono::high_resolution_clock::now();
    const double seconds_since_last_write = std::chrono::duration<double>(t_now - t_prev).count();
    t_prev = t_now;

    // calculate estimated remaining time
    const int estimated_remaining_seconds = std::floor(seconds_since_last_write * static_cast<double>(expected_iterations - iteration) /
                                                       static_cast<double>(every_nth_iteration));

    const size_t percentage =
        std::min(100ul, static_cast<size_t>(100.0 * static_cast<double>(iteration) / static_cast<double>(expected_iterations)));

    printProgress(simulation->params.input_file_path, percentage, iteration, expected_iterations, estimated_remaining_seconds);
}

void ProgressBarInterceptor::onSimulationEnd(size_t iteration) {
    printProgress(simulation->params.input_file_path, 100, expected_iterations, expected_iterations, 0, true);

    std::time_t t_end = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Logger::logger->info("End time: {}", fmt::format("{:%A %Y-%m-%d %H:%M:%S}", fmt::localtime(t_end)));
}

void ProgressBarInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    auto t_end = std::chrono::high_resolution_clock::now();
    const double seconds = std::chrono::duration<double>(t_end - t_start).count();

    Logger::logger->info("{}╟┤{}ProgressBar: {}", indent, ansi_yellow_bold, ansi_end);
}

ProgressBarInterceptor::operator std::string() const { return "ProgressBarInterceptor"; }
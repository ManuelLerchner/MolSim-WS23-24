#include "ProgressBarInterceptor.h"

#include <spdlog/fmt/chrono.h>
#include <sys/ioctl.h>

#include <filesystem>
#include <iostream>

#include "io/logger/Logger.h"
#include "simulation/SimulationParams.h"
#include "utils/FormatTime.h"

int displayed_width(const char* p) {
    int result = 0;
    for (; *p; ++p) {
        if (p[0] == '\e' && p[1] == '[')
            while (*p != 'm')
                if (*p)
                    ++p;
                else
                    throw std::runtime_error("string terminates inside ANSI colour sequence");
        else
            ++result;
    }
    return result;
}

void printProgress(const std::filesystem::path& input_file_path, size_t percentage, size_t iteration, size_t expected_iterations,
                   int estimated_remaining_seconds = -1, double particle_updates_per_second = -1, bool finished = false) {
    struct winsize size {};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    auto should_progress_bar_length = std::min(std::max(size.ws_col - 90, 0), 100);
    auto length_full_progress_bar = static_cast<size_t>(percentage * static_cast<double>(should_progress_bar_length) / 100.0);

    auto progress_bar = fmt::format("[{}{}]", ansi_blue_bold + std::string(length_full_progress_bar, '#'),
                                    std::string(should_progress_bar_length - length_full_progress_bar, ' ') + ansi_end);

    std::string line = fmt::format("{} {}/{} {:>4} ETA: {} MUP/s: {} [{}]", progress_bar, iteration, expected_iterations,
                                   ansi_bright_white_bold + std::to_string(percentage) + "%" + ansi_end,
                                   ansi_bright_white_bold + format_seconds_eta(estimated_remaining_seconds) + ansi_end,
                                   ansi_bright_white_bold + format_mup_s(particle_updates_per_second) + ansi_end,
                                   ansi_bright_white_bold + std::filesystem::path(input_file_path).stem().string() + ansi_end);

    if (displayed_width(line.c_str()) > size.ws_col) {
        line = line.substr(0, size.ws_col - 3) + "...";
    }

    std::cout << "\33[2K\r" << line << std::flush;

    if (finished) {
        std::cout << std::endl;
    }
}

void ProgressBarInterceptor::onSimulationStart(Simulation& simulation) {
    t_start = std::chrono::high_resolution_clock::now();
    t_prev = t_start;

    expected_iterations = static_cast<size_t>(std::ceil(simulation.params.end_time / simulation.params.delta_t));

    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(expected_iterations / 1000.0));

    const size_t percentage = std::min(100ul, static_cast<size_t>(100.0 * static_cast<double>(simulation.params.start_iteration) /
                                                                  static_cast<double>(expected_iterations)));

    last_particle_count = simulation.particle_container->size();
    last_iteration = simulation.params.start_iteration;

    last_remaining_seconds = -1;
    last_particle_updates_per_second = -1;

    Logger::logger->flush();
    printProgress(simulation.params.input_file_path, percentage, simulation.params.start_iteration, expected_iterations, -1, -1);
}

void ProgressBarInterceptor::operator()(size_t iteration, Simulation& simulation) {
    // calculate time since last write
    auto t_now = std::chrono::high_resolution_clock::now();
    const double seconds_since_last_write = std::chrono::duration<double>(t_now - t_prev).count();
    t_prev = t_now;

    // calculate estimated remaining time
    const int estimated_remaining_seconds = std::floor(seconds_since_last_write * static_cast<double>(expected_iterations - iteration) /
                                                       static_cast<double>(every_nth_iteration));

    // calculate percentage
    const size_t percentage =
        std::min(100ul, static_cast<size_t>(100.0 * static_cast<double>(iteration) / static_cast<double>(expected_iterations)));

    // calculate particle updates per second
    size_t current_particle_count = simulation.particle_container->size();
    size_t particle_updates = (current_particle_count + last_particle_count) / 2 * (iteration - last_iteration);

    double particle_updates_per_second = static_cast<double>(particle_updates) / seconds_since_last_write;
    last_particle_count = current_particle_count;
    last_iteration = iteration;

    // Smooth out the estimated remaining time and the updates per second
    if (last_remaining_seconds < 0) last_remaining_seconds = estimated_remaining_seconds;
    if (last_particle_updates_per_second < 0) last_particle_updates_per_second = particle_updates_per_second;

    double smoothed_remaining_seconds = (estimated_remaining_seconds + last_remaining_seconds) / 2;
    double smoothed_particle_updates_per_second = (particle_updates_per_second + last_particle_updates_per_second) / 2;

    printProgress(simulation.params.input_file_path, percentage, iteration, expected_iterations, smoothed_remaining_seconds,
                  smoothed_particle_updates_per_second);

    last_remaining_seconds = smoothed_remaining_seconds;
    last_particle_updates_per_second = smoothed_particle_updates_per_second;
}

void ProgressBarInterceptor::onSimulationEnd(size_t iteration, Simulation& simulation) {
    printProgress(simulation.params.input_file_path, 100, expected_iterations, expected_iterations, 0, -1, true);
}

void ProgressBarInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}ProgressBar: {}", indent, ansi_orange_bold, ansi_end);
    Logger::logger->info("{}║   ├Enabled", indent);
}

ProgressBarInterceptor::operator std::string() const { return ""; }
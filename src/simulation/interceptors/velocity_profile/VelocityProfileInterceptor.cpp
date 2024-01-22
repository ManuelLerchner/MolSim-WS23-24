#include "VelocityProfileInterceptor.h"

#include <chrono>

#include "simulation/SimulationParams.h"
#include "utils/ArrayUtils.h"

VelocityProfileInterceptor::VelocityProfileInterceptor(std::pair<std::array<double, 3>, std::array<double, 3>> box, size_t num_bins,
                                                       size_t sample_every_x_percent)
    : box(box), num_bins(num_bins), sample_every_x_percent(sample_every_x_percent) {}

void VelocityProfileInterceptor::onSimulationStart(Simulation& simulation) {
    bool append = simulation.params.start_iteration != 0;

    csv_writer_x = std::make_unique<CSVWriter>(simulation.params.output_dir_path / "statistics" / "velocity_profile_x_axis.csv", append);
    csv_writer_y = std::make_unique<CSVWriter>(simulation.params.output_dir_path / "statistics" / "velocity_profile_y_axis.csv", append);
    csv_writer_z = std::make_unique<CSVWriter>(simulation.params.output_dir_path / "statistics" / "velocity_profile_z_axis.csv", append);

    bin_width[0] = (box.second[0] - box.first[0]) / num_bins;
    bin_width[1] = (box.second[1] - box.first[1]) / num_bins;
    bin_width[2] = (box.second[2] - box.first[2]) / num_bins;

    csv_writer_x->initialize(
        {"iteration", "bin_index (w= " + std::to_string(bin_width[0]) + ")", "avg_velocity_x", "avg_velocity_y", "avg_velocity_z"});

    csv_writer_y->initialize(
        {"iteration", "bin_index (w= " + std::to_string(bin_width[1]) + ")", "avg_velocity_x", "avg_velocity_y", "avg_velocity_z"});

    csv_writer_z->initialize(
        {"iteration", "bin_index (w= " + std::to_string(bin_width[2]) + ")", "avg_velocity_x", "avg_velocity_y", "avg_velocity_z"});

    auto expected_iterations = static_cast<size_t>(std::ceil(simulation.params.end_time / simulation.params.delta_t));
    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(sample_every_x_percent * expected_iterations / 100));

    if (simulation.params.start_iteration == 0) {
        (*this)(0, simulation);
    }
}

void VelocityProfileInterceptor::operator()(size_t iteration, Simulation& simulation) {
    std::map<size_t, std::array<double, 3>> avg_velocity_per_bin_index_x;
    std::map<size_t, std::array<double, 3>> avg_velocity_per_bin_index_y;
    std::map<size_t, std::array<double, 3>> avg_velocity_per_bin_index_z;

    std::map<size_t, size_t> samples_per_bin_index_x;
    std::map<size_t, size_t> samples_per_bin_index_y;
    std::map<size_t, size_t> samples_per_bin_index_z;

    for (auto& particle : *simulation.particle_container) {
        auto& velocity = particle.getV();
        auto& position = particle.getX();

        // check if particle is in box
        if (position[0] < box.first[0] || position[0] > box.second[0] || position[1] < box.first[1] || position[1] > box.second[1] ||
            position[2] < box.first[2] || position[2] > box.second[2]) {
            continue;
        }

        size_t bin_index_x = std::floor((position[0] - box.first[0]) / bin_width[0]);
        size_t bin_index_y = std::floor((position[1] - box.first[1]) / bin_width[1]);
        size_t bin_index_z = std::floor((position[2] - box.first[2]) / bin_width[2]);

        avg_velocity_per_bin_index_x[bin_index_x] =
            (1.0 / (samples_per_bin_index_x[bin_index_x] + 1)) *
            (samples_per_bin_index_x[bin_index_x] * avg_velocity_per_bin_index_x[bin_index_x] + velocity);

        avg_velocity_per_bin_index_y[bin_index_y] =
            (1.0 / (samples_per_bin_index_y[bin_index_y] + 1)) *
            (samples_per_bin_index_y[bin_index_y] * avg_velocity_per_bin_index_y[bin_index_y] + velocity);

        avg_velocity_per_bin_index_z[bin_index_z] =
            (1.0 / (samples_per_bin_index_z[bin_index_z] + 1)) *
            (samples_per_bin_index_z[bin_index_z] * avg_velocity_per_bin_index_z[bin_index_z] + velocity);

        samples_per_bin_index_x[bin_index_x]++;
        samples_per_bin_index_y[bin_index_y]++;
        samples_per_bin_index_z[bin_index_z]++;
    }

    for (auto& [bin_index, avg_velocity] : avg_velocity_per_bin_index_x) {
        csv_writer_x->writeRow({iteration, bin_index, avg_velocity[0], avg_velocity[1], avg_velocity[2]});
    }

    for (auto& [bin_index, avg_velocity] : avg_velocity_per_bin_index_y) {
        csv_writer_y->writeRow({iteration, bin_index, avg_velocity[0], avg_velocity[1], avg_velocity[2]});
    }

    for (auto& [bin_index, avg_velocity] : avg_velocity_per_bin_index_z) {
        csv_writer_z->writeRow({iteration, bin_index, avg_velocity[0], avg_velocity[1], avg_velocity[2]});
    }
}

void VelocityProfileInterceptor::onSimulationEnd(size_t iteration, Simulation& simulation) {}

void VelocityProfileInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}VelocityProfile: {}", indent, ansi_orange_bold, ansi_end);
    Logger::logger->info("{}║   ┌Observed box: ({}, {}, {}) - ({}, {}, {})", indent, box.first[0], box.first[1], box.first[2],
                         box.second[0], box.second[1], box.second[2]);
    Logger::logger->info("{}║   ├Number of bins per axis: {}", indent, num_bins);
    Logger::logger->info("{}║   └Sample every x percent: {}", indent, sample_every_x_percent);
}

VelocityProfileInterceptor::operator std::string() const {
    return fmt::format("VelocityProfile: num_bins={}, sample_every_x_percent={}", num_bins, sample_every_x_percent);
}

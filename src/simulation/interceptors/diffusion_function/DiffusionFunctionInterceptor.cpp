#include "DiffusionFunctionInterceptor.h"

#include <chrono>
#include <unordered_map>
#include <variant>

#include "simulation/SimulationParams.h"
#include "utils/ArrayUtils.h"

void DiffusionFunctionInterceptor::onSimulationStart(Simulation& simulation) {
    csv_writer = std::make_unique<CSVWriter>(simulation.params.output_dir_path / "statistics" / "diffusion_function.csv");

    csv_writer->initialize({"iteration", "var(t)"});

    auto expected_iterations = static_cast<size_t>(std::ceil(simulation.params.end_time / simulation.params.delta_t) + 1);
    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(sample_every_x_percent * expected_iterations / 100));

    saveCurrentParticlePositions(simulation);
    last_sampled_iteration = 0;
}

void DiffusionFunctionInterceptor::operator()(size_t iteration, Simulation& simulation) {
    if (simulation.particle_container->size() != old_particle_positions.size()) {
        throw std::runtime_error(
            "Particle container size changed during simulation. This is not supported by the diffusion function interceptor.");
    }

    double var_t = calculateCurrentDiffusion(simulation);
    csv_writer->writeRow({iteration, var_t});

    saveCurrentParticlePositions(simulation);
    last_sampled_iteration = iteration;
}

void DiffusionFunctionInterceptor::onSimulationEnd(size_t iteration, Simulation& simulation) {
    if (iteration != last_sampled_iteration) {
        double var_t = calculateCurrentDiffusion(simulation);
        csv_writer->writeRow({iteration, var_t});
    }
}

void DiffusionFunctionInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}DiffusionFunctionInterceptor: {}", indent, ansi_orange_bold, ansi_end);
    Logger::logger->info("{}║   ├Sample every x percent: {}", indent, sample_every_x_percent);
}

DiffusionFunctionInterceptor::operator std::string() const { return ""; }

void DiffusionFunctionInterceptor::saveCurrentParticlePositions(const Simulation& simulation) {
    old_particle_positions.clear();
    for (auto& particle : *simulation.particle_container) {
        old_particle_positions.push_back(particle.getX());
    }
}

double DiffusionFunctionInterceptor::calculateCurrentDiffusion(const Simulation& simulation) const {
    double total_displacement = 0;

    for (size_t i = 0; i < simulation.particle_container->size(); i++) {
        auto& particle = simulation.particle_container->getParticles()[i];
        auto& old_particle_position = old_particle_positions[i];

        std::array<double, 3> displacement = particle.getX() - old_particle_position;

        // detect if particle has moved over the periodic boundary
        if (std::holds_alternative<SimulationParams::LinkedCellsType>(simulation.params.container_type)) {
            auto& container = std::get<SimulationParams::LinkedCellsType>(simulation.params.container_type);
            auto& box_size = container.domain_size;

            for (size_t i = 0; i < 2; i++) {
                if (std::abs(displacement[i]) > box_size[i] / 2) {
                    displacement[i] = box_size[i] - std::abs(displacement[i]);
                }
            }
        }

        double distance = std::pow(ArrayUtils::L2Norm(displacement), 2);

        total_displacement += distance;
    }

    double var_t = total_displacement / simulation.particle_container->size();

    return var_t;
}
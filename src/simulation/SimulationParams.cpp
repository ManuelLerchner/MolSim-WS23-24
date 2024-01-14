#include "SimulationParams.h"

#include <filesystem>
#include <fstream>
#include <numeric>

#include "io/input/chkpt/ChkptPointFileReader.h"
#include "io/logger/Logger.h"
#include "io/output/OutputFormats.h"
#include "physics/ForcePicker.h"
#include "physics/simpleforces/GlobalDownwardsGravity.h"
#include "simulation/SimulationParams.h"
#include "utils/StringUtils.h"

std::filesystem::path constructOutputPath(const std::filesystem::path& base_path, const std::string& name) {
    auto base = base_path;

    if (base.empty()) {
        base = "./output";
    }

    return std::filesystem::absolute(base) / name;
}

SimulationParams::SimulationParams(const std::filesystem::path& input_file_path, double delta_t, double end_time,
                                   const std::variant<DirectSumType, LinkedCellsType>& container_type,
                                   const std::vector<std::shared_ptr<SimulationInterceptor>>& interceptors,
                                   const std::vector<std::shared_ptr<SimpleForceSource>>& simple_forces,
                                   const std::vector<std::shared_ptr<PairwiseForceSource>>& pairwise_forces,
                                   const std::vector<std::shared_ptr<TargettedForceSource>>& targetted_forces, bool fresh,
                                   const std::filesystem::path& base_path)
    : input_file_path(std::filesystem::absolute(input_file_path)),
      delta_t(delta_t),
      end_time(end_time),
      interceptors(interceptors),
      container_type(container_type),
      simple_forces(simple_forces),
      pairwise_forces(pairwise_forces),
      targetted_forces(targetted_forces),
      fresh(fresh) {
    if (end_time < 0) {
        Logger::logger->error("End time must be positive");
        throw std::runtime_error("End time must be positive");
    }
    if (delta_t < 0) {
        Logger::logger->error("Delta t must be positive");
        throw std::runtime_error("Delta t must be positive");
    }

    this->output_dir_path = constructOutputPath(base_path, input_file_path.stem().string());

    this->input_file_hash = ChkptPointFileReader::calculateHash(input_file_path);

    this->num_particles = 0;
}

void SimulationParams::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    std::string force_names =
        std::accumulate(
            simple_forces.begin(), simple_forces.end(), std::string{},
            [](const std::string& acc, const std::shared_ptr<SimpleForceSource>& force) { return acc + std::string(*force) + ", "; }) +
        std::accumulate(
            pairwise_forces.begin(), pairwise_forces.end(), std::string{},
            [](const std::string& acc, const std::shared_ptr<PairwiseForceSource>& force) { return acc + std::string(*force) + ", "; });

    Logger::logger->info("{}╔════════════════════════════════════════", indent);
    Logger::logger->info("{}╟┤{}Simulation arguments: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Input file path: {}", indent, input_file_path.string());
    Logger::logger->info("{}║  Output directory path: {}", indent, output_dir_path.string());
    Logger::logger->info("{}║  Delta_t: {}", indent, delta_t);
    Logger::logger->info("{}║  End_time: {}", indent, end_time);
    Logger::logger->info("{}║  Reuse cached data: {}", indent, !fresh);

    // Print Physical setup
    Logger::logger->info("{}╟┤{}Physical setup: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Number of particles: {}", indent, num_particles);
    Logger::logger->info("{}║  Number of forces: {}", indent, pairwise_forces.size() + simple_forces.size());
    Logger::logger->info("{}║  Forces: {}", indent, force_names);

    Logger::logger->info("{}╟┤{}Container: {}", indent, ansi_yellow_bold, ansi_end);
    if (std::holds_alternative<SimulationParams::LinkedCellsType>(container_type)) {
        auto lc_container = std::get<SimulationParams::LinkedCellsType>(container_type);

        using LC = LinkedCellsContainer;

        auto domain_size = lc_container.domain_size;
        Logger::logger->info("{}║  Linked Cells", indent);
        Logger::logger->info("{}║  Domain size: {} x {} x {}", indent, domain_size[0], domain_size[1], domain_size[2]);
        Logger::logger->info("{}║  Cutoff radius: {}", indent, lc_container.cutoff_radius);
        Logger::logger->info("{}║   ┌Left: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[0]));
        Logger::logger->info("{}║   ├Right: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[1]));
        Logger::logger->info("{}║   ├Bottom: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[2]));
        Logger::logger->info("{}║   ├Top: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[3]));
        Logger::logger->info("{}║   ├Back: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[4]));
        Logger::logger->info("{}║   └Front: {}", indent, LC::boundaryConditionToString(lc_container.boundary_conditions[5]));
    } else if (std::holds_alternative<SimulationParams::DirectSumType>(container_type)) {
        Logger::logger->info("{}║  Direct Sum", indent);
    } else {
        Logger::logger->error("Invalid container type");
        throw std::runtime_error("Invalid container type");
    }

    Logger::logger->info("{}╟┤{}Interceptors: {}", indent, ansi_yellow_bold, ansi_end);
    if (interceptors.empty()) {
        Logger::logger->info("{}║  None", indent);
    } else {
        for (auto& interceptor : interceptors) {
            interceptor->logSummary(depth);
        }
    }

    Logger::logger->info("{}╚════════════════════════════════════════", indent);
}
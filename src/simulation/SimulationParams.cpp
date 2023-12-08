#include "SimulationParams.h"

#include <filesystem>
#include <numeric>

#include "io/logger/Logger.h"
#include "physics/ForcePicker.h"

std::string construct_output_path(const std::string& base_path, const std::string& input_file_path) {
    auto base = base_path;
    if (base_path.empty()) {
        base = "./output/";
    }

    std::filesystem::path input_path{input_file_path};
    return base + std::string(input_path.stem()) + "/";
};

auto convertToForces(const std::vector<std::string>& force_strings) {
    auto supported = ForcePicker::get_supported_forces();

    std::vector<std::shared_ptr<ForceSource>> forces;
    for (auto& force_s : force_strings) {
        if (!supported.contains(force_s)) {
            auto supported_forces = std::string();
            for (auto& [name, force] : supported) {
                supported_forces += name + ", ";
            }

            Logger::logger->error("Invalid force given: {}. Supported forces are: {}", force_s, supported_forces);
            exit(-1);
        }
        forces.push_back(supported[force_s]);
    }
    return forces;
}

auto convertToOutputFormat(const std::string& output_format) {
    auto supported = FileOutputHandler::get_supported_output_formats();

    if (!supported.contains(output_format)) {
        auto supported_formats = std::string();
        for (auto& [name, format] : supported) {
            supported_formats += name + ", ";
        }

        Logger::logger->error("Invalid output format given: {}. Supported output formats are: {}", output_format, supported_formats);
        exit(-1);
    }

    return supported[output_format];
}

SimulationParams::SimulationParams(const std::string& input_file_path, const std::string& output_dir_path, double delta_t, double end_time,
                                   int fps, int video_length, const std::variant<DirectSumType, LinkedCellsType>& container_type,
                                   const std::string& output_format, const std::vector<std::string>& force_strings, bool performance_test,
                                   const std::string& base_path)
    : input_file_path(input_file_path),
      delta_t(delta_t),
      end_time(end_time),
      fps(fps),
      video_length(video_length),
      container_type(container_type),
      forces(convertToForces(force_strings)),
      performance_test(performance_test) {
    if (fps < 0) {
        Logger::logger->error("FPS must be positive");
        exit(-1);
    }
    if (video_length < 0) {
        Logger::logger->error("Video length must be positive");
        exit(-1);
    }
    if (end_time < 0) {
        Logger::logger->error("End time must be positive");
        exit(-1);
    }
    if (delta_t < 0) {
        Logger::logger->error("Delta t must be positive");
        exit(-1);
    }

    this->output_format = convertToOutputFormat(output_format);

    if (output_dir_path.empty()) {
        this->output_dir_path = construct_output_path(base_path, input_file_path);
    } else {
        this->output_dir_path = output_dir_path;
    }
}

void SimulationParams::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    std::string force_names =
        std::accumulate(forces.begin(), forces.end(), std::string{},
                        [](const std::string& acc, const std::shared_ptr<ForceSource>& force) { return acc + std::string(*force) + ", "; });

    Logger::logger->info("{}╔════════════════════════════════════════", indent);
    Logger::logger->info("{}╟┤{}Simulation arguments: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Input file path: {}", indent, input_file_path);
    Logger::logger->info("{}║  Output directory path: {}", indent, output_dir_path);
    Logger::logger->info("{}║  Delta_t: {}", indent, delta_t);
    Logger::logger->info("{}║  End_time: {}", indent, end_time);

    Logger::logger->info("{}╟┤{}Rendering arguments: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Frames per second: {}", indent, fps);
    Logger::logger->info("{}║  Video length: {}", indent, video_length);

    // Print Physical setup
    Logger::logger->info("{}╟┤{}Physical setup: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║  Number of particles: {}", indent, num_particles);
    Logger::logger->info("{}║  Number of forces: {}", indent, forces.size());
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
        exit(-1);
    }

    Logger::logger->info("{}╚════════════════════════════════════════", indent);
}
#include "SimulationParams.h"

#include <filesystem>

#include "io/logger/Logger.h"

std::string construct_output_path(const std::string& input_file_path) {
    std::filesystem::path input_path{input_file_path};
    return "./output/" + std::string(input_path.stem()) + "/";
};

SimulationParams::SimulationParams(const std::string& input_file_path, const std::string& output_dir_path, double delta_t, double end_time,
                                   int fps, int video_length, const std::variant<DirectSumType, LinkedCellsType>& container_type,
                                   const Thermostat& thermostat, const std::string& output_format, bool performance_test)
    : input_file_path(input_file_path),
      delta_t(delta_t),
      end_time(end_time),
      fps(fps),
      video_length(video_length),
      container_type(container_type),
      thermostat(thermostat),
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

    if (output_format == "vtk") {
        this->output_format = FileOutputHandler::OutputFormat::VTK;
    } else if (output_format == "xyz") {
        this->output_format = FileOutputHandler::OutputFormat::XYZ;
    } else if (output_format == "none") {
        this->output_format = FileOutputHandler::OutputFormat::NONE;
    } else {
        Logger::logger->error("Invalid output format given");
        exit(-1);
    }

    if (output_dir_path.empty()) {
        this->output_dir_path = construct_output_path(input_file_path);
    } else {
        this->output_dir_path = output_dir_path;
    }
}
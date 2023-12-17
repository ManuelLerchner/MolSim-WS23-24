#include "SaveFileInterceptor.h"

#include <cmath>
#include <string>

#include "io/logger/Logger.h"

SaveFileInterceptor::SaveFileInterceptor(OutputFormat output_format, int fps, int video_length)
    : output_format(output_format), fps(fps), video_length(video_length) {
    if (fps < 0) {
        Logger::logger->error("FPS must be positive");
        throw std::runtime_error("FPS must be positive");
    }
    if (video_length < 0) {
        Logger::logger->error("Video length must be positive");
        throw std::runtime_error("Video length must be positive");
    }
}

void SaveFileInterceptor::onSimulationStart() {
    size_t expected_iterations = static_cast<size_t>(std::ceil(simulation->params.end_time / simulation->params.delta_t) + 1);

    SimulationInterceptor::every_nth_iteration = std::max(expected_iterations / (fps * video_length), 1ul);

    file_output_handler = std::make_unique<FileOutputHandler>(output_format, simulation->params);

    file_output_handler->writeFile(0, simulation->particle_container);
    file_counter++;
}

void SaveFileInterceptor::operator()(size_t iteration) {
    file_output_handler->writeFile(static_cast<int>(iteration), simulation->particle_container);
    file_counter++;
}

void SaveFileInterceptor::onSimulationEnd(size_t iteration) {
    file_output_handler->writeFile(static_cast<int>(iteration), simulation->particle_container);
    file_counter++;
}

SaveFileInterceptor::operator std::string() const { return "SaveFileInterceptor: " + std::to_string(file_counter) + " files saved"; }
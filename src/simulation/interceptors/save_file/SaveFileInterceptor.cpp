#include "SaveFileInterceptor.h"

#include <cmath>
#include <string>

SaveFileInterceptor::SaveFileInterceptor(Simulation& simulation)
    : SimulationInterceptor(simulation), file_output_handler(simulation.params) {
    size_t expected_iterations = static_cast<size_t>(std::ceil(simulation.params.end_time / simulation.params.delta_t) + 1);

    SimulationInterceptor::every_nth_iteration = std::max(
        expected_iterations / (static_cast<size_t>(simulation.params.fps) * static_cast<size_t>(simulation.params.video_length)), 1ul);
}

void SaveFileInterceptor::onSimulationStart() {
    file_output_handler.writeFile(0, simulation.particle_container);
    file_counter++;
}

void SaveFileInterceptor::operator()(size_t iteration) {
    file_output_handler.writeFile(static_cast<int>(iteration), simulation.particle_container);
    file_counter++;
}

void SaveFileInterceptor::onSimulationEnd(size_t iteration) {
    file_output_handler.writeFile(static_cast<int>(iteration), simulation.particle_container);
    file_counter++;
}

SaveFileInterceptor::operator std::string() const { return "SaveFileInterceptor: " + std::to_string(file_counter) + " files saved"; }
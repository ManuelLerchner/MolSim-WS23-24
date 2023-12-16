#include "SaveFileInterceptor.h"

#include <cmath>
#include <limits>
#include <string>

SaveFileInterceptor::SaveFileInterceptor(Simulation& simulation)
    : SimulationInterceptor(simulation), file_output_handler(simulation.params) {
    size_t expected_iterations = std::floor(simulation.params.end_time / simulation.params.delta_t);

    SimulationInterceptor::every_nth_iteration =
        std::max(expected_iterations / (simulation.params.fps * simulation.params.video_length), 1ul);
}

void SaveFileInterceptor::onSimulationStart() {
    file_output_handler.writeFile(0, simulation.particle_container);
    file_counter++;
}

void SaveFileInterceptor::operator()(int iteration) {
    file_output_handler.writeFile(iteration, simulation.particle_container);
    file_counter++;
}

void SaveFileInterceptor::onSimulationEnd(int iteration) {
    file_output_handler.writeFile(iteration, simulation.particle_container);
    file_counter++;
}

SaveFileInterceptor::operator std::string() const { return "SaveFileInterceptor: " + std::to_string(file_counter) + " files saved"; }
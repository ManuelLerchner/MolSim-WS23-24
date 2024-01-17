#include "TemperatureSensorInterceptor.h"

#include "io/logger/Logger.h"
#include "simulation/SimulationParams.h"

void TemperatureSensorInterceptor::onSimulationStart(Simulation& simulation) {
    bool append = simulation.params.start_iteration != 0;

    csv_writer = std::make_unique<CSVWriter>(simulation.params.output_dir_path / "statistics" / "temperature.csv", append);

    csv_writer->initialize({"iteration", "temperature"});

    auto expected_iterations = static_cast<size_t>(std::ceil(simulation.params.end_time / simulation.params.delta_t) + 1);
    SimulationInterceptor::every_nth_iteration = std::max(1, static_cast<int>(sample_every_x_percent * expected_iterations / 100));

    if (simulation.params.start_iteration == 0) {
        auto current_temperature = thermostat->getCurrentContainerTemperature(simulation.particle_container);
        csv_writer->writeRow({simulation.params.start_iteration, current_temperature});
    }
}

void TemperatureSensorInterceptor::operator()(size_t iteration, Simulation& simulation) {
    const double current_temperature = thermostat->getCurrentContainerTemperature(simulation.particle_container);

    csv_writer->writeRow({iteration, current_temperature});
}

void TemperatureSensorInterceptor::onSimulationEnd(size_t iteration, Simulation& simulation) {
    const double current_temperature = thermostat->getCurrentContainerTemperature(simulation.particle_container);

    csv_writer->writeRow({iteration, current_temperature});
}

void TemperatureSensorInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}TemperatureSensor: {}", indent, ansi_orange_bold, ansi_end);
    Logger::logger->info("{}║   ├Sample every x percent: {}", indent, sample_every_x_percent);
}

TemperatureSensorInterceptor::operator std::string() const { return ""; }
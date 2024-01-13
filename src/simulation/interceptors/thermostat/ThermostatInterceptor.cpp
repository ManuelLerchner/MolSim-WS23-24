#include "ThermostatInterceptor.h"

#include "io/logger/Logger.h"

ThermostatInterceptor::ThermostatInterceptor(std::shared_ptr<Thermostat> thermostat, size_t application_interval) : thermostat(thermostat) {
    SimulationInterceptor::every_nth_iteration = application_interval;
}

void ThermostatInterceptor::onSimulationStart(Simulation& simulation) {}

void ThermostatInterceptor::operator()(size_t iteration, Simulation& simulation) {
    thermostat->scaleTemperature(simulation.particle_container);
}

void ThermostatInterceptor::onSimulationEnd(size_t iteration, Simulation& simulation) {}

void ThermostatInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}Thermostat: {}", indent, ansi_orange_bold, ansi_end);
    Logger::logger->info("{}║   ┌Target temperature: {}", indent, thermostat->getTargetTemperature());
    Logger::logger->info("{}║   ├Maximum temperature change: {}", indent, thermostat->getMaxTemperatureChange());
    Logger::logger->info("{}║   └Application interval: {}", indent, every_nth_iteration);
}

ThermostatInterceptor::operator std::string() const { return ""; }
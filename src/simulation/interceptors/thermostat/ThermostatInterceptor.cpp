#include "ThermostatInterceptor.h"

#include "io/logger/Logger.h"

ThermostatInterceptor::ThermostatInterceptor(Thermostat& thermostat) : thermostat(thermostat) {
    SimulationInterceptor::every_nth_iteration = thermostat.getApplicationInterval();
}

void ThermostatInterceptor::onSimulationStart() {}

void ThermostatInterceptor::operator()(size_t iteration) { thermostat.scaleTemperature(simulation->particle_container); }

void ThermostatInterceptor::onSimulationEnd(size_t iteration) {}

void ThermostatInterceptor::logSummary(int depth) const {
    std::string indent = std::string(depth * 2, ' ');

    Logger::logger->info("{}╟┤{}Thermostat: {}", indent, ansi_yellow_bold, ansi_end);
    Logger::logger->info("{}║   ┌Target temperature: {}", indent, thermostat.getTargetTemperature());
    Logger::logger->info("{}║   ├Maximum temperature change: {}", indent, thermostat.getMaxTemperatureChange());
    Logger::logger->info("{}║   └Application interval: {}", indent, thermostat.getApplicationInterval());
}

ThermostatInterceptor::operator std::string() const { return "ThermostatInterceptor"; }
#include "ThermostatInterceptor.h"

ThermostatInterceptor::ThermostatInterceptor(Thermostat& thermostat) : thermostat(thermostat) {
    SimulationInterceptor::every_nth_iteration = thermostat.getApplicationInterval();
}

void ThermostatInterceptor::onSimulationStart() {}

void ThermostatInterceptor::operator()(size_t iteration) { thermostat.scaleTemperature(simulation->particle_container); }

void ThermostatInterceptor::onSimulationEnd(size_t iteration) {}

ThermostatInterceptor::operator std::string() const { return "ThermostatInterceptor"; }
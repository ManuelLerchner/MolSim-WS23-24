#include "ThermostatInterceptor.h"

ThermostatInterceptor::ThermostatInterceptor(Simulation& simulation) : SimulationInterceptor(simulation) {
    SimulationInterceptor::every_nth_iteration = simulation.params.thermostat->getApplicationInterval();
}

void ThermostatInterceptor::onSimulationStart() {}

void ThermostatInterceptor::operator()(size_t iteration) { simulation.params.thermostat->scaleTemperature(simulation.particle_container); }

void ThermostatInterceptor::onSimulationEnd(size_t iteration) {}

ThermostatInterceptor::operator std::string() const { return "ThermostatInterceptor"; }
#include "ThermostatInterceptor.h"

ThermostatInterceptor::ThermostatInterceptor(Simulation& simulation) : SimulationInterceptor(simulation) {
    SimulationInterceptor::every_nth_iteration = simulation.params.thermostat->getApplicationInterval();
}

void ThermostatInterceptor::onSimulationStart() {}

void ThermostatInterceptor::operator()(int iteration) { simulation.params.thermostat->scaleTemperature(simulation.particle_container); }

void ThermostatInterceptor::onSimulationEnd(int iteration) {}

ThermostatInterceptor::operator std::string() const { return "ThermostatInterceptor"; }
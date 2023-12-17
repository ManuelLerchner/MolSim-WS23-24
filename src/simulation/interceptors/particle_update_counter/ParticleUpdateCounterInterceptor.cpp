#include "ParticleUpdateCounterInterceptor.h"

#include <chrono>

ParticleUpdateCounterInterceptor::ParticleUpdateCounterInterceptor(Simulation& simulation) : SimulationInterceptor(simulation) {
    SimulationInterceptor::every_nth_iteration = 1;
}

void ParticleUpdateCounterInterceptor::onSimulationStart() {
    particle_updates = 0;
    t_start = std::chrono::high_resolution_clock::now();
}

void ParticleUpdateCounterInterceptor::operator()(int iteration) { particle_updates += simulation.particle_container->size(); }

void ParticleUpdateCounterInterceptor::onSimulationEnd(int iteration) {
    t_end = std::chrono::high_resolution_clock::now();
    t_diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();

    particle_updates_per_second = 1000.0 * static_cast<double>(particle_updates) / static_cast<double>(t_diff);
}

double ParticleUpdateCounterInterceptor::getParticleUpdatesPerSecond() const { return particle_updates_per_second; }


std::chrono::milliseconds::rep ParticleUpdateCounterInterceptor::getSimulationDurationMS() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}


ParticleUpdateCounterInterceptor::operator std::string() const {
    return "ParticleUpdateInterceptor: " + std::to_string(particle_updates_per_second) + " particle updates per second";
}
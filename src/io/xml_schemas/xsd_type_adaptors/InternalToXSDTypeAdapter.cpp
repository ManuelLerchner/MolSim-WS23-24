#include "InternalToXSDTypeAdapter.h"

ParticleType InternalToXSDTypeAdapter::convertToParticle(const Particle& particle) {
    auto position = convertToVector(particle.getX());
    auto velocity = convertToVector(particle.getV());
    auto force = convertToVector(particle.getF());
    auto old_force = convertToVector(particle.getOldF());
    auto mass = particle.getM();
    auto type = particle.getType();
    auto epsilon = particle.getEpsilon();
    auto sigma = particle.getSigma();
    auto locked = particle.isLocked();
    auto connected_particles = convertToConnectedParticles(particle.getConnectedParticles());

    auto particle_type = ParticleType{position, velocity, force, old_force, mass, type, epsilon, sigma, locked, connected_particles};

    return particle_type;
}

DoubleVec3Type InternalToXSDTypeAdapter::convertToVector(const std::array<double, 3>& vector) {
    return DoubleVec3Type{vector[0], vector[1], vector[2]};
}

ConnectedParticlesType InternalToXSDTypeAdapter::convertToConnectedParticles(
    const std::vector<std::tuple<long, double, double>>& connected_particles) {
    ConnectedParticlesType xsd_connected_particles{};

    for (const auto& entry : connected_particles) {
        xsd_connected_particles.entries().push_back(convertToConnectedParticleEntry(entry));
    }

    return xsd_connected_particles;
}

ConnectedParticleEntryType InternalToXSDTypeAdapter::convertToConnectedParticleEntry(const std::tuple<long, double, double>& entry) {
    return ConnectedParticleEntryType{std::get<0>(entry), std::get<1>(entry), std::get<2>(entry)};
}

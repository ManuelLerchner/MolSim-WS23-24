#include "XSDToInternalTypeAdapter.h"

#include "io/logger/Logger.h"

CuboidSpawner XSDToInternalTypeAdapter::convertToCuboidSpawner(const CuboidSpawnerType& cuboid, bool third_dimension) {
    auto lower_left_front_corner = convertToVector(cuboid.lower_left_front_corner());
    auto grid_dimensions = convertToVector(cuboid.grid_dim());
    auto initial_velocity = convertToVector(cuboid.velocity());

    auto grid_spacing = cuboid.grid_spacing();
    auto mass = cuboid.mass();
    auto type = cuboid.type();
    auto temperature = cuboid.temperature();

    if (grid_dimensions[0] <= 0 || grid_dimensions[1] <= 0 || grid_dimensions[2] <= 0) {
        Logger::logger->error("Cuboid grid dimensions must be positive");
        exit(-1);
    }

    if (!third_dimension && grid_dimensions[2] > 1) {
        Logger::logger->error("Cuboid grid dimensions must be 1 in z direction if third dimension is disabled");
        exit(-1);
    }

    if (grid_spacing <= 0) {
        Logger::logger->error("Cuboid grid spacing must be positive");
        exit(-1);
    }

    if (mass <= 0) {
        Logger::logger->error("Cuboid mass must be positive");
        exit(-1);
    }

    if (temperature < 0) {
        Logger::logger->error("Cuboid temperature must be positive");
        exit(-1);
    }

    return CuboidSpawner{lower_left_front_corner, grid_dimensions,        grid_spacing,    mass,
                         initial_velocity,        static_cast<int>(type), third_dimension, temperature};
}

SphereSpawner XSDToInternalTypeAdapter::convertToSphereSpawner(const SphereSpawnerType& sphere, bool third_dimension) {
    auto center = convertToVector(sphere.center());
    auto initial_velocity = convertToVector(sphere.velocity());

    auto radius = sphere.radius();
    auto grid_spacing = sphere.grid_spacing();
    auto mass = sphere.mass();
    auto type = sphere.type();
    auto temperature = sphere.temperature();

    if (radius <= 0) {
        Logger::logger->error("Sphere radius must be positive");
        exit(-1);
    }

    if (grid_spacing <= 0) {
        Logger::logger->error("Sphere grid spacing must be positive");
        exit(-1);
    }

    if (mass <= 0) {
        Logger::logger->error("Sphere mass must be positive");
        exit(-1);
    }

    if (temperature < 0) {
        Logger::logger->error("Sphere temperature must be positive");
        exit(-1);
    }

    return SphereSpawner{center,           static_cast<int>(radius), grid_spacing,    mass,
                         initial_velocity, static_cast<int>(type),   third_dimension, temperature};
}

CuboidSpawner XSDToInternalTypeAdapter::convertToSingleParticleSpawner(const SingleParticleSpawnerType& particle, bool third_dimension) {
    auto position = convertToVector(particle.position());
    auto initial_velocity = convertToVector(particle.velocity());

    auto mass = particle.mass();
    auto type = particle.type();

    return CuboidSpawner{position, {1, 1, 1}, 0, mass, initial_velocity, static_cast<int>(type), third_dimension, particle.temperature()};
}

std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType> XSDToInternalTypeAdapter::convertToParticleContainer(
    const ParticleContainerType& particle_container) {
    std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType> container;

    if (particle_container.linkedcells_container().present()) {
        auto container_data = *particle_container.linkedcells_container();

        auto domain_size = XSDToInternalTypeAdapter::convertToVector(container_data.domain_size());
        auto cutoff_radius = container_data.cutoff_radius();
        auto boundary_conditions = XSDToInternalTypeAdapter::convertToBoundaryConditionsArray(container_data.boundary_conditions());

        container = SimulationParams::LinkedCellsType(domain_size, cutoff_radius, boundary_conditions);
    } else if (particle_container.directsum_container().present()) {
        container = SimulationParams::DirectSumType();
    } else {
        Logger::logger->error("Container type not implemented");
        exit(-1);
    }

    return container;
}

std::array<LinkedCellsContainer::BoundaryCondition, 6> XSDToInternalTypeAdapter::convertToBoundaryConditionsArray(
    const BoundaryConditionsType& boundary) {
    std::array<LinkedCellsContainer::BoundaryCondition, 6> boundary_conditions;

    boundary_conditions[0] = convertToBoundaryCondition(boundary.left());
    boundary_conditions[1] = convertToBoundaryCondition(boundary.right());
    boundary_conditions[2] = convertToBoundaryCondition(boundary.bottom());
    boundary_conditions[3] = convertToBoundaryCondition(boundary.top());
    boundary_conditions[4] = convertToBoundaryCondition(boundary.back());
    boundary_conditions[5] = convertToBoundaryCondition(boundary.front());

    return boundary_conditions;
}

LinkedCellsContainer::BoundaryCondition XSDToInternalTypeAdapter::convertToBoundaryCondition(const BoundaryType& boundary) {
    switch (boundary) {
        case BoundaryType::value::Outflow:
            return LinkedCellsContainer::BoundaryCondition::OUTFLOW;
        case BoundaryType::value::Reflective:
            return LinkedCellsContainer::BoundaryCondition::REFLECTIVE;
        default:
            Logger::logger->error("Boundary condition not implemented");
            exit(-1);
    }
}

Particle XSDToInternalTypeAdapter::convertToParticle(const ParticleType& particle) {
    auto position = XSDToInternalTypeAdapter::convertToVector(particle.position());
    auto velocity = XSDToInternalTypeAdapter::convertToVector(particle.velocity());
    auto force = XSDToInternalTypeAdapter::convertToVector(particle.force());
    auto old_force = XSDToInternalTypeAdapter::convertToVector(particle.old_force());
    auto type = particle.type();
    auto mass = particle.mass();

    if (mass <= 0) {
        Logger::logger->error("Particle mass must be positive");
        exit(-1);
    }

    return Particle{position, velocity, force, old_force, mass, static_cast<int>(type)};
}

std::vector<std::string> XSDToInternalTypeAdapter::convertToForces(const SettingsType::force_sequence& forces) {
    std::vector<std::string> force_sources;

    for (ForcesType force : forces) {
        std::string force_name = ForcesType::_xsd_ForcesType_literals_[force];

        force_sources.push_back(force_name);
    }

    return force_sources;
}

std::array<double, 3> XSDToInternalTypeAdapter::convertToVector(const DoubleVec3Type& vector) {
    return {vector.x(), vector.y(), vector.z()};
}

std::array<int, 3> XSDToInternalTypeAdapter::convertToVector(const IntVec3Type& vector) { return {vector.x(), vector.y(), vector.z()}; }

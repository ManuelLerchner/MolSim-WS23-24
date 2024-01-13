#include "XSDToInternalTypeAdapter.h"

#include "io/logger/Logger.h"
#include "physics/pairwiseforces/GravitationalForce.h"
#include "physics/pairwiseforces/LennardJonesForce.h"
#include "physics/pairwiseforces/LennardJonesRepulsiveForce.h"
#include "physics/pairwiseforces/SmoothedLennardJonesForce.h"
#include "physics/simpleforces/GlobalDownwardsGravity.h"
#include "physics/simpleforces/HarmonicForce.h"
#include "physics/targettedforces/TargettedTemporaryConstantForce.h"
#include "simulation/interceptors/diffusion_function/DiffusionFunctionInterceptor.h"
#include "simulation/interceptors/frame_writer/FrameWriterInterceptor.h"
#include "simulation/interceptors/particle_update_counter/ParticleUpdateCounterInterceptor.h"
#include "simulation/interceptors/progress_bar/ProgressBarInterceptor.h"
#include "simulation/interceptors/radial_distribution_function/RadialDistributionFunctionInterceptor.h"
#include "simulation/interceptors/temperature_sensor/TemperatureSensorInterceptor.h"
#include "simulation/interceptors/thermostat/ThermostatInterceptor.h"

CuboidSpawner XSDToInternalTypeAdapter::convertToCuboidSpawner(const CuboidSpawnerType& cuboid, bool third_dimension) {
    auto lower_left_front_corner = convertToVector(cuboid.lower_left_front_corner());
    auto grid_dimensions = convertToVector(cuboid.grid_dim());
    auto initial_velocity = convertToVector(cuboid.velocity());

    auto grid_spacing = cuboid.grid_spacing();
    auto mass = cuboid.mass();
    auto type = cuboid.type();
    auto epsilon = cuboid.epsilon();
    auto sigma = cuboid.sigma();
    auto temperature = cuboid.temperature();

    if (grid_dimensions[0] <= 0 || grid_dimensions[1] <= 0 || grid_dimensions[2] <= 0) {
        Logger::logger->error("Cuboid grid dimensions must be positive");
        throw std::runtime_error("Cuboid grid dimensions must be positive");
    }

    if (!third_dimension && grid_dimensions[2] > 1) {
        Logger::logger->error("Cuboid grid dimensions must be 1 in z direction if third dimension is disabled");
        throw std::runtime_error("Cuboid grid dimensions must be 1 in z direction if third dimension is disabled");
    }

    if (grid_spacing <= 0) {
        Logger::logger->error("Cuboid grid spacing must be positive");
        throw std::runtime_error("Cuboid grid spacing must be positive");
    }

    if (mass <= 0) {
        Logger::logger->error("Cuboid mass must be positive");
        throw std::runtime_error("Cuboid mass must be positive");
    }

    if (temperature < 0) {
        Logger::logger->error("Cuboid temperature must be positive");
        throw std::runtime_error("Cuboid temperature must be positive");
    }

    return CuboidSpawner{
        lower_left_front_corner, grid_dimensions, grid_spacing, mass, initial_velocity, static_cast<int>(type), epsilon, sigma,
        third_dimension,         temperature};
}

SoftBodyCuboidSpawner XSDToInternalTypeAdapter::convertToSoftBodyCuboidSpawner(const SoftBodySpawnerType& soft_body_cuboid,
                                                                               bool third_dimension) {
    auto lower_left_front_corner = convertToVector(soft_body_cuboid.lower_left_front_corner());
    auto grid_dimensions = convertToVector(soft_body_cuboid.grid_dim());
    auto initial_velocity = convertToVector(soft_body_cuboid.velocity());

    auto grid_spacing = soft_body_cuboid.grid_spacing();
    auto mass = soft_body_cuboid.mass();
    auto type = soft_body_cuboid.type();
    auto spring_constant = soft_body_cuboid.spring_constant();
    auto epsilon = soft_body_cuboid.epsilon();
    auto sigma = soft_body_cuboid.sigma();
    auto temperature = soft_body_cuboid.temperature();

    if (grid_dimensions[0] <= 0 || grid_dimensions[1] <= 0 || grid_dimensions[2] <= 0) {
        Logger::logger->error("Cuboid grid dimensions must be positive");
        throw std::runtime_error("Cuboid grid dimensions must be positive");
    }

    if (!third_dimension && grid_dimensions[2] > 1) {
        Logger::logger->error("Cuboid grid dimensions must be 1 in z direction if third dimension is disabled");
        throw std::runtime_error("Cuboid grid dimensions must be 1 in z direction if third dimension is disabled");
    }

    if (grid_spacing <= 0) {
        Logger::logger->error("Cuboid grid spacing must be positive");
        throw std::runtime_error("Cuboid grid spacing must be positive");
    }

    if (mass <= 0) {
        Logger::logger->error("Cuboid mass must be positive");
        throw std::runtime_error("Cuboid mass must be positive");
    }

    if (temperature < 0) {
        Logger::logger->error("Cuboid temperature must be positive");
        throw std::runtime_error("Cuboid temperature must be positive");
    }

    return SoftBodyCuboidSpawner{lower_left_front_corner, grid_dimensions,        grid_spacing, mass,
                                 initial_velocity,        static_cast<int>(type), epsilon,      sigma,
                                 spring_constant,         third_dimension,        temperature};
}

SphereSpawner XSDToInternalTypeAdapter::convertToSphereSpawner(const SphereSpawnerType& sphere, bool third_dimension) {
    auto center = convertToVector(sphere.center());
    auto initial_velocity = convertToVector(sphere.velocity());

    auto radius = sphere.radius();
    auto grid_spacing = sphere.grid_spacing();
    auto mass = sphere.mass();
    auto type = sphere.type();
    auto epsilon = sphere.epsilon();
    auto sigma = sphere.sigma();
    auto temperature = sphere.temperature();

    if (radius <= 0) {
        Logger::logger->error("Sphere radius must be positive");
        throw std::runtime_error("Sphere radius must be positive");
    }

    if (grid_spacing <= 0) {
        Logger::logger->error("Sphere grid spacing must be positive");
        throw std::runtime_error("Sphere grid spacing must be positive");
    }

    if (mass <= 0) {
        Logger::logger->error("Sphere mass must be positive");
        throw std::runtime_error("Sphere mass must be positive");
    }

    if (temperature < 0) {
        Logger::logger->error("Sphere temperature must be positive");
        throw std::runtime_error("Sphere temperature must be positive");
    }

    return SphereSpawner{center, static_cast<int>(radius), grid_spacing, mass, initial_velocity, static_cast<int>(type), epsilon,
                         sigma,  third_dimension,          temperature};
}

CuboidSpawner XSDToInternalTypeAdapter::convertToSingleParticleSpawner(const SingleParticleSpawnerType& particle, bool third_dimension) {
    auto position = convertToVector(particle.position());
    auto initial_velocity = convertToVector(particle.velocity());

    auto mass = particle.mass();
    auto type = particle.type();
    auto epsilon = particle.epsilon();
    auto sigma = particle.sigma();

    return CuboidSpawner{
        position, {1, 1, 1}, 0, mass, initial_velocity, static_cast<int>(type), epsilon, sigma, third_dimension, particle.temperature()};
}

std::vector<std::shared_ptr<SimulationInterceptor>> XSDToInternalTypeAdapter::convertToSimulationInterceptors(
    const SimulationInterceptorsType& interceptors, bool third_dimension) {
    std::vector<std::shared_ptr<SimulationInterceptor>> simulation_interceptors;

    if (interceptors.Thermostat()) {
        auto xsd_thermostat = *interceptors.Thermostat();

        auto thermostat = convertToThermostat(xsd_thermostat, third_dimension);
        simulation_interceptors.push_back(std::make_shared<ThermostatInterceptor>(thermostat));

        if (xsd_thermostat.temperature_sensor()) {
            auto temperature_sensor = *xsd_thermostat.temperature_sensor();
            auto sample_every_x_percent = temperature_sensor.sample_every_x_percent();

            simulation_interceptors.push_back(std::make_shared<TemperatureSensorInterceptor>(thermostat, sample_every_x_percent));
        }
    }

    if (interceptors.ParticleUpdatesPerSecond()) {
        simulation_interceptors.push_back(std::make_shared<ParticleUpdateCounterInterceptor>());
    }

    if (interceptors.DiffusionFunction()) {
        auto sample_every_x_percent = interceptors.DiffusionFunction()->sample_every_x_percent();
        simulation_interceptors.push_back(std::make_shared<DiffusionFunctionInterceptor>(sample_every_x_percent));
    }

    if (interceptors.RadialDistributionFunction()) {
        auto bin_width = interceptors.RadialDistributionFunction()->bin_width();
        auto sample_every_x_percent = interceptors.RadialDistributionFunction()->sample_every_x_percent();

        simulation_interceptors.push_back(std::make_shared<RadialDistributionFunctionInterceptor>(bin_width, sample_every_x_percent));
    }

    if (interceptors.FrameWriter()) {
        auto fps = interceptors.FrameWriter()->fps();
        auto video_length = interceptors.FrameWriter()->video_length_s();
        auto output_format = convertToOutputFormat(interceptors.FrameWriter()->output_format());

        simulation_interceptors.push_back(std::make_shared<FrameWriterInterceptor>(output_format, fps, video_length));
    }

    simulation_interceptors.push_back(std::make_shared<ProgressBarInterceptor>());

    return simulation_interceptors;
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
        throw std::runtime_error("Container type not implemented");
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
        case BoundaryType::value::Periodic:
            return LinkedCellsContainer::BoundaryCondition::PERIODIC;
        default:
            Logger::logger->error("Boundary condition not implemented");
            throw std::runtime_error("Boundary condition not implemented");
    }
}

Thermostat XSDToInternalTypeAdapter::convertToThermostat(const ThermostatInterceptorType& thermostat, bool third_dimension) {
    auto target_temperature = thermostat.target_temperature();
    auto max_temperature_change = thermostat.max_temperature_change();
    auto application_interval = thermostat.application_interval();

    if (target_temperature < 0) {
        Logger::logger->error("Target temperature must be positive");
        throw std::runtime_error("Target temperature must be positive");
    }

    if (max_temperature_change < 0) {
        Logger::logger->error("Max temperature change must be an absolute value (positive)");
        throw std::runtime_error("Max temperature change must be an absolute value (positive)");
    }

    if (application_interval <= 0) {
        Logger::logger->error("Application interval must be a positive integer > 0");
        throw std::runtime_error("Application interval must be a positive integer > 0");
    }

    return Thermostat{target_temperature, max_temperature_change, static_cast<size_t>(application_interval), third_dimension};
}

Particle XSDToInternalTypeAdapter::convertToParticle(const ParticleType& particle) {
    auto position = XSDToInternalTypeAdapter::convertToVector(particle.position());
    auto velocity = XSDToInternalTypeAdapter::convertToVector(particle.velocity());
    auto force = XSDToInternalTypeAdapter::convertToVector(particle.force());
    auto old_force = XSDToInternalTypeAdapter::convertToVector(particle.old_force());
    auto type = particle.type();
    auto mass = particle.mass();
    auto epsilon = particle.epsilon();
    auto sigma = particle.sigma();

    if (mass <= 0) {
        Logger::logger->error("Particle mass must be positive");
        throw std::runtime_error("Particle mass must be positive");
    }

    return Particle{position, velocity, force, old_force, mass, static_cast<int>(type), epsilon, sigma};
}

std::tuple<std::vector<std::shared_ptr<SimpleForceSource>>, std::vector<std::shared_ptr<PairwiseForceSource>>,
           std::vector<std::shared_ptr<TargettedForceSource>>>
XSDToInternalTypeAdapter::convertToForces(
    const ForcesType& forces, const std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType>& container_data) {
    std::vector<std::shared_ptr<SimpleForceSource>> simple_force_sources;
    std::vector<std::shared_ptr<PairwiseForceSource>> pairwise_force_sources;
    std::vector<std::shared_ptr<TargettedForceSource>> targetted_force_sources;

    // Simple Forces
    if (forces.GlobalDownwardsGravity()) {
        auto g = (*forces.GlobalDownwardsGravity()).g();
        simple_force_sources.push_back(std::make_shared<GlobalDownwardsGravity>(g));
    }
    if (forces.HarmonicPotential()) {
        simple_force_sources.push_back(std::make_shared<HarmonicForce>(container_data));
    }

    // Pairwise Forces
    if (forces.LennardJones()) {
        pairwise_force_sources.push_back(std::make_shared<LennardJonesForce>());
    }
    if (forces.LennardJonesRepulsive()) {
        pairwise_force_sources.push_back(std::make_shared<LennardJonesRepulsiveForce>());
    }
    if (forces.SmoothedLennardJones()) {
        double r_c = (*forces.SmoothedLennardJones()).r_c();
        double r_l = (*forces.SmoothedLennardJones()).r_l();
        pairwise_force_sources.push_back(std::make_shared<SmoothedLennardJonesForce>(r_c, r_l));
    }
    if (forces.Gravitational()) {
        pairwise_force_sources.push_back(std::make_shared<GravitationalForce>());
    }

    // Targetted Forces
    if (forces.TargettedTemporaryConstant()) {
        auto indices_list = forces.TargettedTemporaryConstant()->indices();
        std::vector<size_t> indices_vector;
        for (auto& index : indices_list) {
            indices_vector.push_back(index);
        }
        auto force = convertToVector(forces.TargettedTemporaryConstant()->force());
        auto start_time = forces.TargettedTemporaryConstant()->start_time();
        auto end_time = forces.TargettedTemporaryConstant()->end_time();

        targetted_force_sources.push_back(std::make_shared<TargettedTemporaryConstantForce>(indices_vector, force, start_time, end_time));
    }

    return {simple_force_sources, pairwise_force_sources, targetted_force_sources};
}

std::array<double, 3> XSDToInternalTypeAdapter::convertToVector(const DoubleVec3Type& vector) {
    return {vector.x(), vector.y(), vector.z()};
}

std::array<int, 3> XSDToInternalTypeAdapter::convertToVector(const IntVec3Type& vector) { return {vector.x(), vector.y(), vector.z()}; }

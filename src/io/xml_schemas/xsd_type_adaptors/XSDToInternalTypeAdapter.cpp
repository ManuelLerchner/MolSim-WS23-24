#include "XSDToInternalTypeAdapter.h"

#include <variant>

#include "io/logger/Logger.h"
#include "physics/pairwiseforces/GravitationalForce.h"
#include "physics/pairwiseforces/LennardJonesForce.h"
#include "physics/pairwiseforces/SmoothedLennardJonesForce.h"
#include "physics/simpleforces/GlobalDownwardsGravity.h"
#include "physics/thermostats/absolute_thermostat/AbsoluteThermostat.h"
#include "physics/thermostats/relative_thermostat/RelativeThermostat.h"
#include "simulation/interceptors/diffusion_function/DiffusionFunctionInterceptor.h"
#include "simulation/interceptors/frame_writer/FrameWriterInterceptor.h"
#include "simulation/interceptors/particle_update_counter/ParticleUpdateCounterInterceptor.h"
#include "simulation/interceptors/progress_bar/ProgressBarInterceptor.h"
#include "simulation/interceptors/radial_distribution_function/RadialDistributionFunctionInterceptor.h"
#include "simulation/interceptors/temperature_sensor/TemperatureSensorInterceptor.h"
#include "simulation/interceptors/thermostat/ThermostatInterceptor.h"
#include "simulation/interceptors/velocity_profile/VelocityProfileInterceptor.h"

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
    auto locked = cuboid.is_locked();

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
        lower_left_front_corner, grid_dimensions, grid_spacing, mass, initial_velocity, static_cast<int>(type), epsilon, sigma, locked,
        third_dimension,         temperature};
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
    auto locked = sphere.is_locked();

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

    return SphereSpawner{center, static_cast<int>(radius), grid_spacing, mass, initial_velocity, static_cast<int>(type), epsilon, sigma,
                         locked, third_dimension,          temperature};
}

CuboidSpawner XSDToInternalTypeAdapter::convertToSingleParticleSpawner(const SingleParticleSpawnerType& particle, bool third_dimension) {
    auto position = convertToVector(particle.position());
    auto initial_velocity = convertToVector(particle.velocity());

    auto mass = particle.mass();
    auto type = particle.type();
    auto epsilon = particle.epsilon();
    auto sigma = particle.sigma();
    auto locked = particle.is_locked();

    return CuboidSpawner{position,
                         {1, 1, 1},
                         0,
                         mass,
                         initial_velocity,
                         static_cast<int>(type),
                         epsilon,
                         sigma,
                         locked,
                         third_dimension,
                         particle.temperature()};
}

std::vector<std::shared_ptr<SimulationInterceptor>> XSDToInternalTypeAdapter::convertToSimulationInterceptors(
    const SimulationInterceptorsType& interceptors, bool third_dimension,
    std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType> container_type) {
    std::vector<std::shared_ptr<SimulationInterceptor>> simulation_interceptors;

    if (interceptors.FrameWriter()) {
        auto fps = interceptors.FrameWriter()->fps();
        auto video_length = interceptors.FrameWriter()->video_length_s();
        auto output_format = convertToOutputFormat(interceptors.FrameWriter()->output_format());

        simulation_interceptors.push_back(std::make_shared<FrameWriterInterceptor>(output_format, fps, video_length));
    }

    if (interceptors.Thermostat()) {
        auto xsd_thermostat = *interceptors.Thermostat();
        auto target_temperature = xsd_thermostat.target_temperature();
        auto max_temperature_change = xsd_thermostat.max_temperature_change();
        auto application_interval = xsd_thermostat.application_interval();

        std::shared_ptr<Thermostat> thermostat;

        if (xsd_thermostat.type() == ThermostatType::value::absolute) {
            thermostat = std::make_shared<AbsoluteThermostat>(target_temperature, max_temperature_change, third_dimension);
        } else if (xsd_thermostat.type() == ThermostatType::value::relative_motion) {
            thermostat = std::make_shared<RelativeThermostat>(target_temperature, max_temperature_change, third_dimension);
        } else {
            Logger::logger->error("Thermostat type not implemented");
            throw std::runtime_error("Thermostat type not implemented");
        }

        simulation_interceptors.push_back(std::make_shared<ThermostatInterceptor>(thermostat, application_interval));

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
        auto xsd_rdf = *interceptors.RadialDistributionFunction();
        auto bin_width = xsd_rdf.bin_width();
        auto sample_every_x_percent = xsd_rdf.sample_every_x_percent();

        simulation_interceptors.push_back(std::make_shared<RadialDistributionFunctionInterceptor>(bin_width, sample_every_x_percent));
    }

    if (interceptors.VelocityProfile()) {
        auto xsd_vp = *interceptors.VelocityProfile();
        auto num_bins = xsd_vp.num_bins();
        auto sample_every_x_percent = xsd_vp.sample_every_x_percent();

        auto box_xsd = xsd_vp.box();

        std::pair<std::array<double, 3>, std::array<double, 3>> box;

        if (box_xsd.present()) {
            auto box_data = *box_xsd;

            auto bottom_left = convertToVector(box_data.lower_left_front_corner());
            auto top_right = convertToVector(box_data.upper_right_back_corner());

            box = std::make_pair(bottom_left, top_right);
        } else {
            std::visit(
                [&box](auto&& container) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(container)>, SimulationParams::DirectSumType>) {
                        Logger::logger->error("Box must be specified if direct sum is used");
                        throw std::runtime_error("Box must be specified if direct sum is used");
                    } else if constexpr (std::is_same_v<std::decay_t<decltype(container)>, SimulationParams::LinkedCellsType>) {
                        auto bottom_left = std::array<double, 3>{0, 0, 0};
                        auto top_right = container.domain_size;

                        box = std::make_pair(bottom_left, top_right);
                    } else {
                        Logger::logger->error("Container type not implemented");
                        throw std::runtime_error("Container type not implemented");
                    }
                },
                container_type);
        }

        simulation_interceptors.push_back(std::make_shared<VelocityProfileInterceptor>(box, num_bins, sample_every_x_percent));
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

Particle XSDToInternalTypeAdapter::convertToParticle(const ParticleType& particle) {
    auto position = XSDToInternalTypeAdapter::convertToVector(particle.position());
    auto velocity = XSDToInternalTypeAdapter::convertToVector(particle.velocity());
    auto force = XSDToInternalTypeAdapter::convertToVector(particle.force());
    auto old_force = XSDToInternalTypeAdapter::convertToVector(particle.old_force());
    auto type = particle.type();
    auto mass = particle.mass();
    auto epsilon = particle.epsilon();
    auto sigma = particle.sigma();
    auto locked = particle.is_locked();

    if (mass <= 0) {
        Logger::logger->error("Particle mass must be positive");
        throw std::runtime_error("Particle mass must be positive");
    }

    return Particle{position, velocity, force, old_force, mass, static_cast<int>(type), epsilon, sigma, locked};
}

std::tuple<std::vector<std::shared_ptr<SimpleForceSource>>, std::vector<std::shared_ptr<PairwiseForceSource>>>
XSDToInternalTypeAdapter::convertToForces(const ForcesType& forces) {
    std::vector<std::shared_ptr<SimpleForceSource>> simple_force_sources;
    std::vector<std::shared_ptr<PairwiseForceSource>> pairwise_force_sources;

    if (forces.LennardJones()) {
        pairwise_force_sources.push_back(std::make_shared<LennardJonesForce>());
    }
    if (forces.SmoothedLennardJones()) {
        double r_c = (*forces.SmoothedLennardJones()).r_c();
        double r_l = (*forces.SmoothedLennardJones()).r_l();
        pairwise_force_sources.push_back(std::make_shared<SmoothedLennardJonesForce>(r_c, r_l));
    }
    if (forces.Gravitational()) {
        pairwise_force_sources.push_back(std::make_shared<GravitationalForce>());
    }
    if (forces.GlobalDownwardsGravity()) {
        auto g = (*forces.GlobalDownwardsGravity()).g();
        simple_force_sources.push_back(std::make_shared<GlobalDownwardsGravity>(g));
    }

    return {simple_force_sources, pairwise_force_sources};
}

std::array<double, 3> XSDToInternalTypeAdapter::convertToVector(const DoubleVec3Type& vector) {
    return {vector.x(), vector.y(), vector.z()};
}

std::array<int, 3> XSDToInternalTypeAdapter::convertToVector(const IntVec3Type& vector) { return {vector.x(), vector.y(), vector.z()}; }

#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "io/xml_schemas/checkpoint/checkpoint_schema.h"
#include "io/xml_schemas/simulation_input/simulation_input_schema.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "particles/spawners/soft_body_cuboid/SoftBodyCuboidSpawner.h"
#include "particles/spawners/sphere/SphereSpawner.h"
#include "simulation/SimulationParams.h"

/**
 * @brief Class to convert XSD types to internal types
 */
class XSDToInternalTypeAdapter {
   public:
    /**
     * @brief Converts a cuboid from the XSD format to the internal format
     *
     * @param cuboid Cuboid in the XSD format
     * @param third_dimension Whether the third dimension is enabled
     * @return CuboidSpawner parsed from the given cuboid in the XSD format
     */
    static CuboidSpawner convertToCuboidSpawner(const CuboidSpawnerType& cuboid, bool third_dimension);

    /**
     * @brief Converts a soft body cuboid from the XSD format to the internal format
     *
     * @param soft_body_cuboid Soft body cuboid in the XSD format
     * @param third_dimension Whether the third dimension is enabled
     * @return SoftBodyCuboidSpawner parsed from the given soft body cuboid in the XSD format
     */
    static SoftBodyCuboidSpawner convertToSoftBodyCuboidSpawner(const SoftBodySpawnerType& soft_body_cuboid, bool third_dimension);

    /**
     * @brief Converts a sphere from the XSD format to the internal format
     *
     * @param sphere Sphere in the XSD format
     * @param third_dimension Whether the third dimension is enabled
     * @return SphereSpawner parsed from the given sphere in the XSD format
     */
    static SphereSpawner convertToSphereSpawner(const SphereSpawnerType& sphere, bool third_dimension);

    /**
     * @brief Converts a particle from the XSD format to the internal format
     *
     * @param particle Particle in the XSD format
     * @param third_dimension Whether the third dimension is enabled
     * @return Particle parsed from the given particle in the XSD format
     */
    static CuboidSpawner convertToSingleParticleSpawner(const SingleParticleSpawnerType& particle, bool third_dimension);

    /**
     * @brief Converts the simulation interceptors from the XSD format to the internal format
     *
     * @param interceptors Simulation interceptors in the XSD format
     * @param third_dimension Whether the third dimension is enabled
     * @param container_type Container type
     * @return List of simulation interceptors parsed from the given simulation interceptors in the XSD format
     */
    static std::vector<std::shared_ptr<SimulationInterceptor>> convertToSimulationInterceptors(
        const SimulationInterceptorsType& interceptors, bool third_dimension,
        std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType> container_type);

    /**
     * @brief Converts a container type from the XSD format to the internal format
     *
     * @param container_type Container type in the XSD format
     * @return ContainerType parsed from the given container type in the XSD format
     */
    static std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType> convertToParticleContainer(
        const ParticleContainerType& container_type);

    /**
     * @brief Converts a boundary conditions type from the XSD format to the internal format
     *
     * @param boundary Boundary conditions type in the XSD format
     * @return BoundaryConditionsArray parsed from the given boundary conditions type in the XSD format
     */
    static std::array<LinkedCellsContainer::BoundaryCondition, 6> convertToBoundaryConditionsArray(const BoundaryConditionsType& boundary);

    /**
     * @brief Converts a boundary type from the XSD format to the internal format
     *
     * @param boundary Boundary condition in the XSD format
     * @return BoundaryCondition parsed from the given boundary type in the XSD format
     */
    static LinkedCellsContainer::BoundaryCondition convertToBoundaryCondition(const BoundaryType& boundary);

    /**
     * @brief Converts a particle type from the XSD format to the internal format
     *
     * @param particle Particle in the XSD format
     * @return Particle parsed from the given particle in the XSD format
     */
    static Particle convertToParticle(const ParticleType& particle);

    /**
     * @brief Converts a force type from the XSD format to the internal format
     *
     * @param forces List of forces in the XSD format
     * @param container_data Container data as a variant of DirectSumType and LinkedCellsType
     * @return Tuple with lists of simple and pairwise forces parsed from the given list of forces in the XSD format
     */
    static std::tuple<std::vector<std::shared_ptr<SimpleForceSource>>, std::vector<std::shared_ptr<PairwiseForceSource>>,
                      std::vector<std::shared_ptr<TargettedForceSource>>>
    convertToForces(const ForcesType& forces,
                    const std::variant<SimulationParams::DirectSumType, SimulationParams::LinkedCellsType>& container_data);

    /**
     * @brief Converts a double vector from the XSD format to the internal format
     *
     * @param vector double Vector in the XSD format
     * @return Vector parsed from the given vector in the XSD format
     */
    static std::array<double, 3> convertToVector(const DoubleVec3Type& vector);

    /**
     * @brief Converts a int vector from the XSD format to the internal format
     *
     * @param vector int Vector in the XSD format
     * @return Vector parsed from the given vector in the XSD format
     */
    static std::array<int, 3> convertToVector(const IntVec3Type& vector);
};
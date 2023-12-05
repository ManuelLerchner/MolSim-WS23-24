#pragma once

#include <variant>

#include "io/output/checkpoint/parser/checkpoint_schema.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "particles/spawners/sphere/SphereSpawner.h"
#include "simulation/SimulationParams.h"

class InternalToXSDTypeAdapter {
   public:
    static ParticleType convertToParticle(const Particle& particle);

    static DoubleVec3Type convertToVector(const std::array<double, 3>& vector);

    static IntVec3Type convertToVector(const std::array<int, 3>& vector);
};
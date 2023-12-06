#pragma once

#include "io/output/chkpt/parser/checkpoint_schema.h"
#include "particles/Particle.h"

class InternalToXSDTypeAdapter {
   public:
    static ParticleType convertToParticle(const Particle& particle);

    static DoubleVec3Type convertToVector(const std::array<double, 3>& vector);

    static IntVec3Type convertToVector(const std::array<int, 3>& vector);
};
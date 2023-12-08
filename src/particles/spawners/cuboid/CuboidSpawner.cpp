#include "CuboidSpawner.h"

#include "utils/ArrayUtils.h"
#include "utils/MaxwellBoltzmannDistribution.h"

CuboidSpawner::CuboidSpawner(const std::array<double, 3>& lower_left_corner, const std::array<int, 3>& grid_dimensions, double grid_spacing,
                             double mass, const std::array<double, 3>& initial_velocity, int type, bool third_dimension,
                             double avg_velocity)
    : lower_left_corner(lower_left_corner),
      grid_dimensions(grid_dimensions),
      grid_spacing(grid_spacing),
      mass(mass),
      type(type),
      initial_velocity(initial_velocity),
      third_dimension(third_dimension),
      avg_velocity(avg_velocity) {}

int CuboidSpawner::spawnParticles(std::vector<Particle>& particle_container) const {
    particle_container.reserve(particle_container.size() + getEstimatedNumberOfParticles());
    int num_particles_spawned = 0;
    for (int i = 0; i < grid_dimensions[0]; i++) {
        for (int j = 0; j < grid_dimensions[1]; j++) {
            for (int k = 0; k < grid_dimensions[2]; k++) {
                const auto grid_pos = std::array<double, 3>{static_cast<double>(i), static_cast<double>(j), static_cast<double>(k)};

                const auto x = lower_left_corner + grid_spacing * grid_pos;
                const auto v = initial_velocity + maxwellBoltzmannDistributedVelocity(avg_velocity, third_dimension ? 3 : 2);

                particle_container.emplace_back(x, v, mass, type);
                num_particles_spawned++;
            }
        }
    }
    return num_particles_spawned;
}

size_t CuboidSpawner::getEstimatedNumberOfParticles() const {
    return static_cast<size_t>(grid_dimensions[0]) * grid_dimensions[1] * grid_dimensions[2];
}
#include "SoftBodyCuboidSpawner.h"

#include <memory>

#include "particles/Particle.h"
#include "particles/spawners/cuboid/CuboidSpawner.h"
#include "physics/thermostats/Thermostat.h"
#include "utils/ArrayUtils.h"

SoftBodyCuboidSpawner::SoftBodyCuboidSpawner(const std::array<double, 3>& lower_left_corner, const std::array<int, 3>& grid_dimensions,
                                             double grid_spacing, double mass, const std::array<double, 3>& initial_velocity, int type,
                                             double epsilon, double sigma, double spring_constant, bool third_dimension,
                                             double initial_temperature)
    : lower_left_corner(lower_left_corner),
      grid_dimensions(grid_dimensions),
      grid_spacing(grid_spacing),
      mass(mass),
      type(type),
      epsilon(epsilon),
      sigma(sigma),
      spring_constant(spring_constant),
      initial_velocity(initial_velocity),
      initial_temperature(initial_temperature),
      third_dimension(third_dimension) {}

int SoftBodyCuboidSpawner::spawnParticles(std::vector<Particle>& particles) const {
    auto prev_size = particles.size();
    particles.reserve(particles.size() + getEstimatedNumberOfParticles());
    for (int i = 0; i < grid_dimensions[0]; i++) {
        for (int j = 0; j < grid_dimensions[1]; j++) {
            for (int k = 0; k < grid_dimensions[2]; k++) {
                const auto grid_pos = std::array<double, 3>{static_cast<double>(i), static_cast<double>(j), static_cast<double>(k)};

                const auto x = lower_left_corner + grid_spacing * grid_pos;

                Particle particle(x, initial_velocity, mass, type, epsilon, sigma);
                Thermostat::setParticleTemperature(initial_temperature, particle, third_dimension ? 3 : 2);
                particles.push_back(std::move(particle));
            }
        }
    }

    auto particle_pos_to_index = [this, &prev_size](const std::array<int, 3>& grid_pos) {
        if (grid_pos[0] < 0 || grid_pos[0] >= grid_dimensions[0] || grid_pos[1] < 0 || grid_pos[1] >= grid_dimensions[1] ||
            grid_pos[2] < 0 || grid_pos[2] >= grid_dimensions[2]) {
            return -1;
        }

        return static_cast<int>(prev_size) + grid_pos[2] + grid_dimensions[2] * grid_pos[1] +
               grid_dimensions[2] * grid_dimensions[1] * grid_pos[0];
    };

    // connect particles with harmonic springs
    for (int i = 0; i < grid_dimensions[0]; i++) {
        for (int j = 0; j < grid_dimensions[1]; j++) {
            for (int k = 0; k < grid_dimensions[2]; k++) {
                auto curr_index = particle_pos_to_index({i, j, k});
                auto& curr_particle = particles[curr_index];

                for (int l = -1; l <= 1; l++) {
                    for (int m = -1; m <= 1; m++) {
                        for (int n = -1; n <= 1; n++) {
                            if (l == 0 && m == 0 && n == 0) {
                                continue;
                            }

                            auto neighbor_index = particle_pos_to_index({i + l, j + m, k + n});

                            if (neighbor_index == -1) {
                                continue;
                            }

                            auto& neighbor_particle = particles[neighbor_index];

                            auto initial_distance = ArrayUtils::L2Norm(curr_particle.getX() - neighbor_particle.getX());

                            curr_particle.addConnectedParticle(&neighbor_particle, initial_distance, spring_constant);
                        }
                    }
                }
            }
        }
    }

    return grid_dimensions[0] * grid_dimensions[1] * grid_dimensions[2];
}

size_t SoftBodyCuboidSpawner::getEstimatedNumberOfParticles() const {
    return static_cast<size_t>(grid_dimensions[0]) * grid_dimensions[1] * grid_dimensions[2];
}

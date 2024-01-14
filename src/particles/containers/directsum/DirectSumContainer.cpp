#include "DirectSumContainer.h"

#include <omp.h>

#include "utils/ArrayUtils.h"

DirectSumContainer::DirectSumContainer(int n) { particles.reserve(n); }

void DirectSumContainer::reserve(size_t n) { particles.reserve(n); }

std::size_t DirectSumContainer::size() const { return particles.size(); }

std::size_t DirectSumContainer::capacity() const { return particles.capacity(); }

void DirectSumContainer::addParticle(const Particle& p) { particles.push_back(p); }

void DirectSumContainer::addParticle(Particle&& p) { particles.push_back(std::move(p)); }

Particle& DirectSumContainer::operator[](int i) { return particles[i]; }

std::vector<Particle>::iterator DirectSumContainer::begin() { return particles.begin(); }

std::vector<Particle>::iterator DirectSumContainer::end() { return particles.end(); }

std::vector<Particle>::const_iterator DirectSumContainer::begin() const { return particles.begin(); }

std::vector<Particle>::const_iterator DirectSumContainer::end() const { return particles.end(); }

const std::vector<Particle>& DirectSumContainer::getParticles() const { return particles; }

void DirectSumContainer::prepareForceCalculation() {}

void DirectSumContainer::applySimpleForces(const std::vector<std::shared_ptr<SimpleForceSource>>& simple_force_sources) {
    for (auto& p : particles) {
        if (p.isLocked()) continue;
        for (auto& force : simple_force_sources) {
            p.setF(p.getF() + force->calculateForce(p));
        }
    }
}

void DirectSumContainer::applyPairwiseForces(const std::vector<std::shared_ptr<PairwiseForceSource>>& force_sources) {
#pragma omp parallel for
    for (auto it1 = particles.begin(); it1 != particles.end(); ++it1) {
        std::array<double, 3> total_force{0, 0, 0};

        for (auto it2 = particles.begin(); it2 != particles.end(); ++it2) {
            if (it1 == it2) continue;
            if (it1->isLocked() && it2->isLocked()) continue;
            for (auto& force : force_sources) {
                total_force = total_force + force->calculateForce(*it1, *it2);
            }
        }
        it1->setF(it1->getF() + total_force);
    }
}

void DirectSumContainer::applyTargettedForces(const std::vector<std::shared_ptr<TargettedForceSource>>& force_sources,
                                              double curr_simulation_time) {
    for (const auto& force_source : force_sources) {
        force_source->applyForce(particles, curr_simulation_time);
    }
}

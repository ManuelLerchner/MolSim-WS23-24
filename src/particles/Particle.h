/**
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "utils/Enums.h"

/**
 * @brief Class to represent a particle
 *
 * Class to represent a particle.
 * A particle has a position, a velocity, a mass and a type.
 * Additionally, the current and previous force exerted on the particle is stored.
 */
class Particle {
   private:
    /**
     * @brief Position of the particle
     */
    std::array<double, 3> x{};

    /**
     * @brief Velocity of the particle
     */
    std::array<double, 3> v{};

    /**
     * @brief Force effective on this particle
     */
    std::array<double, 3> f{};

    /**
     * @brief Force which was effective on this particle
     */
    std::array<double, 3> old_f{};

    /**
     * @brief Mass of this particle
     */
    double m;

    /**
     * @brief Type of the particle. Use it for whatever you want (e.g. to separate molecules belonging to different bodies, matters, and so
     * on)
     */
    int type;

    /**
     * @brief Lennard-Jones potential parameter epsilon
     */
    double epsilon;

    /**
     * @brief Lennard-Jones potential parameter sigma
     */
    double sigma;

    /**
     * @brief Wheter the particle is loccked in space
     */
    LockState lock_state;

    /**
     * @brief List of connected particles
     *
     * List of connected particles. Each entry is a tuple of a weak pointer to the connected particle, and the prefered distance between the
     * the particles and the spring constant. The prefered distance is the distance at which the spring force is zero.
     *
     * entry = (ptr_diff, l_0, k)
     */
    std::vector<std::tuple<long, double, double>> connected_particles;

   public:
    Particle(const Particle& other);

    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg, int type = 0, double epsilon_arg = 1.0,
             double sigma_arg = 1.2, LockState lock_state = LockState::UNLOCKED);

    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, std::array<double, 3> f_arg, std::array<double, 3> old_f_arg,
             double m_arg, int type = 0, double epsilon_arg = 1.0, double sigma_arg = 1.2, LockState lock_state = LockState::UNLOCKED);

    virtual ~Particle();

    /**
     * @brief Sets the position of the particle
     *
     * @param x New position
     */
    inline void setX(const std::array<double, 3>& x) { this->x = x; }

    /**
     * @brief Sets the velocity of the particle
     *
     * @param v New velocity
     */
    inline void setV(const std::array<double, 3>& v) { this->v = v; }

    /**
     * @brief Sets the force of the particle
     *
     * @param f New force
     */
    inline void setF(const std::array<double, 3>& f) { this->f = f; }

    /**
     * @brief Sets the old force of the particle
     *
     * @param oldF New old force
     */
    inline void setOldF(const std::array<double, 3>& oldF) { old_f = oldF; }

    /**
     * @brief Gets the position of the particle
     */
    [[nodiscard]] inline const std::array<double, 3>& getX() const { return x; }

    /**
     * @brief Gets the velocity of the particle
     */
    [[nodiscard]] inline const std::array<double, 3>& getV() const { return v; }

    /**
     * @brief Gets the total force of the particle
     */
    [[nodiscard]] inline const std::array<double, 3>& getF() const { return f; }

    /**
     * @brief Gets the old total force of the particle
     */
    [[nodiscard]] inline const std::array<double, 3>& getOldF() const { return old_f; }

    /**
     * @brief Gets the mass of the particle
     */
    [[nodiscard]] inline double getM() const { return m; }

    /**
     * @brief Gets the type of the particle
     */
    [[nodiscard]] inline int getType() const { return type; }

    /**
     * @brief Gets the Lennard-Jones potential parameter epsilon
     */
    [[nodiscard]] inline double getEpsilon() const { return epsilon; }

    /**
     * @brief Gets the Lennard-Jones potential parameter sigma
     */
    [[nodiscard]] inline double getSigma() const { return sigma; }

    /**
     * @brief Set wheter the particle is locked in space
     */
    inline void setLocked(LockState new_lock_state) { lock_state = new_lock_state; }

    /**
     * @brief Gets whether the particle is locked in space
     */
    [[nodiscard]] inline bool isLocked() const { return lock_state == LockState::LOCKED; }

    /**
     * @brief Gets the list of connected particles
     */
    [[nodiscard]] inline std::vector<std::tuple<long, double, double>>& getConnectedParticles() { return connected_particles; }

    /**
     * @brief Adds a connected particle
     *
     * @param ptr_diff
     * @param l_0 Prefered distance between the particles
     * @param k Spring constant
     */
    void addConnectedParticle(long ptr_diff, double l_0, double k);

    bool operator==(Particle& other);

    bool operator==(const Particle& other) const;

    [[nodiscard]] std::string toString() const;
};

std::ostream& operator<<(std::ostream& stream, Particle& p);

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
    void setX(const std::array<double, 3>& x);

    /**
     * @brief Sets the velocity of the particle
     *
     * @param v New velocity
     */
    void setV(const std::array<double, 3>& v);

    /**
     * @brief Sets the force of the particle
     *
     * @param f New force
     */
    void setF(const std::array<double, 3>& f);

    /**
     * @brief Sets the old force of the particle
     *
     * @param oldF New old force
     */
    void setOldF(const std::array<double, 3>& oldF);

    /**
     * @brief Gets the position of the particle
     */
    [[nodiscard]] const std::array<double, 3>& getX() const;

    /**
     * @brief Gets the velocity of the particle
     */
    [[nodiscard]] const std::array<double, 3>& getV() const;

    /**
     * @brief Gets the total force of the particle
     */
    [[nodiscard]] const std::array<double, 3>& getF() const;

    /**
     * @brief Gets the old total force of the particle
     */
    [[nodiscard]] const std::array<double, 3>& getOldF() const;

    /**
     * @brief Gets the mass of the particle
     */
    [[nodiscard]] double getM() const;

    /**
     * @brief Gets the type of the particle
     */
    [[nodiscard]] int getType() const;

    /**
     * @brief Gets the Lennard-Jones potential parameter epsilon
     */
    [[nodiscard]] double getEpsilon() const;

    /**
     * @brief Gets the Lennard-Jones potential parameter sigma
     */
    [[nodiscard]] double getSigma() const;

    /**
     * @brief Set wheter the particle is locked in space
     */
    void setLocked(LockState new_lock_state);

    /**
     * @brief Gets whether the particle is locked in space
     */
    [[nodiscard]] bool isLocked() const;

    /**
     * @brief Gets the list of connected particles
     */
    [[nodiscard]] std::vector<std::tuple<long, double, double>>& getConnectedParticles();

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

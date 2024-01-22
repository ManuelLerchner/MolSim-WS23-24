#pragma once

/**
 * @brief Enum class to define the dimension count of the simulation (2D or 3D). Affects primarily the dimensionality of particle spawners
 * and temperature-based velocity initialization.
 */
enum class ThirdDimension { DISABLED, ENABLED };

/**
 * @brief Enum class to define the lockstate of particles. Locked particles are not allowed to move.
 */
enum class LockState { UNLOCKED, LOCKED };
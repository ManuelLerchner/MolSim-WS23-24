#include <array>

#include "TargettedForceSource.h"

/**
 * @brief Class for a constant force source
 *
 * Class for a constant force source, which exerts a constant force on the particles with the specified indices.
 */
class TargettedTemporaryConstantForce : public TargettedForceSource {
   private:
    /**
     * @brief Force exerted on the particles
     */
    const std::array<double, 3> force;

    /**
     * @brief Start Time within the simulation from which on the force is exerted
     */
    const double start_time;

    /**
     * @brief End Time within the simulation until which the force is exerted
     */
    const double end_time;

   public:
    /**
     * @brief Construct a new Targetted Temporary Constant Force object
     *
     * @param targetIndices Indices of the particles on which the force is applied
     * @param force Force exerted on the particles
     * @param start_time Time for which the force is exerted
     * @param end_time Time until which the force is exerted
     */
    TargettedTemporaryConstantForce(const std::vector<size_t>& targetIndices, const std::array<double, 3>& force, double start_time,
                                    double end_time);

    /**
     * @brief Applies the force directly to the particles with the specified indices within the vector
     *
     * @param particle_vector Particle vector on which the force is applied
     * @param curr_simulation_time Current simulation time
     *
     * Calculates and applies the force exerted on the particles identified by index within the given particle vector.
     */
    void applyForce(std::vector<Particle>& particle_vector, double curr_simulation_time) const override;

    /**
     * @brief Conversion from a force source object to a string containing its name
     */
    explicit operator std::string() const override;
};
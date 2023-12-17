#pragma once

#include <functional>

#include "simulation/Simulation.h"

class SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Simulation Interceptor object
     */
    explicit SimulationInterceptor(Simulation& simulation) : simulation(simulation) {}

    virtual ~SimulationInterceptor() = default;

    /**
     * @brief Called before the simulation loop starts
     */
    virtual void onSimulationStart() = 0;

    /**
     * @brief Called on every nth iteration. This function should perform the
     * desired action.
     *
     * @param iteration The current iteration
     */
    virtual void operator()(size_t iteration) = 0;

    /**
     * @brief Called after the simulation loop ends
     *
     * @param iteration The current iteration
     */
    virtual void onSimulationEnd(size_t iteration) = 0;

    /**
     * @brief This function is called by the simulation loop on every iteration.
     * Whenever the iteration is a multiple of every_nth_iteration, the
     * operator() function is called.
     *
     * @param iteration The current iteration
     * @see operator()
     */
    void notify(size_t iteration) {
        if (iteration % every_nth_iteration == 0) {
            (*this)(iteration);
        }
    }

     /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    virtual explicit operator std::string() const = 0;

   protected:
    const Simulation& simulation;
    size_t every_nth_iteration = 1;
};
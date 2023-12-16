#pragma once
#include <chrono>

#include "io/output/FileOutputHandler.h"
#include "simulation/interceptors/SimulationInterceptor.h"

class SaveFileInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Save File Interceptor object
     */
    SaveFileInterceptor(Simulation& simulation);

    /**
     * @brief This function saves the initial state of the simulation
     */
    void onSimulationStart();

    /**
     * @brief This function is called on every nth iteration. It writes the current
     * state of the simulation to a file.
     *
     * @param iteration The current iteration
     */
    void operator()(int iteration);

    /**
     * @brief This function saves the final state of the simulation
     *
     * @param iteration The current iteration
     */
    void onSimulationEnd(int iteration);

    /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    operator std::string() const;

   private:
    size_t file_counter = 0;
    FileOutputHandler file_output_handler;
};
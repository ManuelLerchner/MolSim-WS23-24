#pragma once
#include <chrono>
#include <memory>

#include "io/output/csv/CSVWriter.h"
#include "simulation/interceptors/SimulationInterceptor.h"

class VelocityProfileInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Thermostat Interceptor object
     */
    VelocityProfileInterceptor(std::pair<std::array<double, 3>, std::array<double, 3>> box, size_t num_bins, size_t sample_every_x_percent);

    /**
     * @brief This function is sets the particle_updates to 0 and initializes
     * the start time of the simulation
     *
     * @param simulation The simulation object
     */
    void onSimulationStart(Simulation& simulation) override;

    /**
     * @brief This function is called on every nth iteration. It counts the
     * number of particle updates which have been performed.
     *
     * @param iteration The current iteration
     * @param simulation The simulation object
     */
    void operator()(size_t iteration, Simulation& simulation) override;

    /**
     * @brief This function is empty as the thermostat doesnt need to do anything
     * at the end of the simulation
     *
     * @param iteration The current iteration
     * @param simulation The simulation object
     */
    void onSimulationEnd(size_t iteration, Simulation& simulation) override;

    /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    explicit operator std::string() const override;

    /**
     * @brief Logs the summary of the radial distribution function
     */
    void logSummary(int depth) const override;

   private:
    std::pair<std::array<double, 3>, std::array<double, 3>> box;
    size_t num_bins;
    std::array<double, 3> bin_width;
    size_t sample_every_x_percent;
    std::unique_ptr<CSVWriter> csv_writer_x;
    std::unique_ptr<CSVWriter> csv_writer_y;
    std::unique_ptr<CSVWriter> csv_writer_z;
};
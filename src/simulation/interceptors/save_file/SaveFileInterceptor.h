#pragma once
#include <chrono>

#include "io/output/FileOutputHandler.h"
#include "io/output/OutputFormats.h"
#include "simulation/interceptors/SimulationInterceptor.h"

class SaveFileInterceptor : public SimulationInterceptor {
   public:
    /**
     * @brief Construct a new Save File Interceptor object
     */
    SaveFileInterceptor(OutputFormat output_format, int fps, int video_length);

    /**
     * @brief This function saves the initial state of the simulation
     */
    void onSimulationStart() override;

    /**
     * @brief This function is called on every nth iteration. It writes the current
     * state of the simulation to a file.
     *
     * @param iteration The current iteration
     */
    void operator()(size_t iteration) override;

    /**
     * @brief This function saves the final state of the simulation
     *
     * @param iteration The current iteration
     */
    void onSimulationEnd(size_t iteration) override;

    /**
     * @brief The string representation of this interceptor
     *
     * @return std::string
     *
     * This is used to write the final summary of the Interceptors to the
     * console.
     */
    explicit operator std::string() const override;

   private:
    size_t file_counter = 0;
    std::unique_ptr<FileOutputHandler> file_output_handler;
    OutputFormat output_format;
    size_t fps;
    size_t video_length;
};
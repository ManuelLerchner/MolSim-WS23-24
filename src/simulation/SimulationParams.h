#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include "io/output/FileOutputHandler.h"
#include "particles/containers/linkedcells/LinkedCellsContainer.h"
#include "physics/ForceSource.h"

/**
 * @brief Contains all parameters needed to run a simulation.
 *
 * This class is used to pass the parameters from the input file / CLI to the Simulation class.
 */
class SimulationParams {
   public:
    /**
     * @brief Struct to specify the type of the particle container as DirectSumType
     */
    struct DirectSumType {
        operator std::string() const { return "DirectSum"; }
    };

    /**
     * @brief Struct to specify the type of the particle container as LinkedCellsType (needs domain_size and cutoff_radius)
     */
    struct LinkedCellsType {
        std::array<double, 3> domain_size;
        double cutoff_radius;
        std::array<LinkedCellsContainer::BoundaryCondition, 6> boundary_conditions;

        LinkedCellsType() = delete;
        LinkedCellsType(const std::array<double, 3>& domain_size, double cutoff_radius,
                        const std::array<LinkedCellsContainer::BoundaryCondition, 6>& boundary_conditions)
            : domain_size(domain_size), cutoff_radius(cutoff_radius), boundary_conditions(boundary_conditions) {}

        operator std::string() const {
            return "LinkedCells ([" + std::to_string(domain_size[0]) + "x" + std::to_string(domain_size[1]) + "x" +
                   std::to_string(domain_size[2]) + "];" + std::to_string(cutoff_radius) + ";[" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[0]) + "|" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[1]) + "|" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[2]) + "|" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[3]) + "|" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[4]) + "|" +
                   LinkedCellsContainer::boundaryConditionToString(boundary_conditions[5]) + "])";
        }
    };

    /**
     * @brief Path to the input file of the simulation
     */
    std::string input_file_path;

    /**
     * @brief Path to the directory in which to save the simulation output
     */
    std::string output_dir_path;

    /**
     * @brief Time step of a single simulation iteration
     */
    double delta_t;

    /**
     * @brief End time of the simulation
     */
    double end_time;

    /**
     * @brief Frames per second at which to save the simulation. This is used to calculate how often to save the simulation data
     */
    int fps;

    /**
     * @brief Expected length of the simulation video in seconds. This is used to calculate how often to save the simulation data
     */
    int video_length;

    /**
     * @brief Type of the particle container
     */
    std::variant<DirectSumType, LinkedCellsType> container_type;

    /**
     * @brief Forces to be applied to the particles
     */
    std::vector<std::shared_ptr<ForceSource>> forces;

    /**
     * @brief Whether to run the simulation in performance test mode
     */
    bool performance_test;

    /**
     * @brief Output file format of the simulation
     */
    FileOutputHandler::OutputFormat output_format;

    /**
     * @brief Construct a new SimulationParams object
     *
     * @param input_file_path Path to the input file of the simulation
     * @param output_dir_path Path to the directory in which to save the simulation output
     * @param delta_t Time step of a single simulation iteration
     * @param end_time End time of the simulation
     * @param fps Frames per second at which to save the simulation. This is used to calculate how often to save the simulation data
     * @param video_length Expected length of the simulation video in seconds. This is used to calculate how often to save the
     * simulation data
     * @param container_type Type of the particle container
     * @param output_format Output file format of the simulation
     * @param force_strings Forces to be applied to the particles
     * @param performance_test Whether to run the simulation in performance test mode
     */
    SimulationParams(const std::string& input_file_path, const std::string& output_dir_path, double delta_t, double end_time, int fps,
                     int video_length, const std::variant<DirectSumType, LinkedCellsType>& container_type, const std::string& output_format,
                     const std::vector<std::string>& force_strings, bool performance_test);

    /**
     * @brief Dissallow default construction of a SimulationParams object (would have invalid values for a simulation)
     */
    SimulationParams() = delete;
};
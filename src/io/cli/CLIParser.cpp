#include "CLIParser.h"

#include "io/logger/Logger.h"
#include "spdlog/sinks/rotating_file_sink.h"

CLIParams parse_arguments(int argc, char* argv[]) {
    bool performance_test = false;
    bool fresh = false;

    std::filesystem::path input_file_path;
    std::string log_level = "info";
    std::string log_output = "std";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            std::cout << "Allowed options:\n"
                         "--input_file_path,-f  The path to the input file. Must be specified, otherwise the program will terminate.\n"
                         "--log_level,-l        The log level. Possible values: trace, debug, info, warning, error, critical, off\n"
                         "--performance_test,-p Run the simulation in performance test mode\n"
                         "--log_output          You can only choose between the output options std(only cl output) and file (only file "
                         "output). Default: no file output\n"
                         "--fresh               Rerun the simulation from scratch without using any cached data. This will delete the "
                         "whole output directory.\n";
            exit(0);
        } else if (arg == "--input_file_path" || arg == "-f") {
            if (i + 1 < argc) {
                input_file_path = argv[++i];
            } else {
                std::cerr << "Error: --input_file_path requires an argument." << std::endl;
                exit(-1);
            }
        } else if (arg == "--log_level" || arg == "-l") {
            if (i + 1 < argc) {
                log_level = argv[++i];
            } else {
                std::cerr << "Error: --log_level requires an argument." << std::endl;
                exit(-1);
            }
        } else if (arg == "--performance_test" || arg == "-p") {
            performance_test = true;
        } else if (arg == "--log_output") {
            if (i + 1 < argc) {
                log_output = argv[++i];
            } else {
                std::cerr << "Error: --log_output requires an argument." << std::endl;
                exit(-1);
            }
        } else if (arg == "--fresh") {
            fresh = true;
        } else {
            input_file_path = arg;
        }
    }

    if (log_output == "std" || log_output == "STD") {
        Logger::logger->info("Using std output");
    } else if (log_output == "file" || log_output == "FILE") {
        Logger::init_logger(Logger::LogType::FILE);
        Logger::logger->info("Using file output");
    } else {
        std::cerr << "Error: Invalid log output given. Options: no file output: 'std' and file output: 'file'" << std::endl;
        exit(-1);
    }

    Logger::update_level(log_level);

    if (input_file_path.empty()) {
        std::cerr << "Error: No input file path given." << std::endl;
        exit(-1);
    }

    return CLIParams{input_file_path, performance_test, fresh};
}

SimulationParams merge_parameters(const CLIParams& params_cli, const std::optional<SimulationParams>& file_params) {
    if (!file_params) {
        Logger::logger->warn("No simulation parameters provided. Try using a XML file as input.");
        throw std::runtime_error("No simulation parameters provided. Try using a XML file as input.");
    }

    SimulationParams params = *file_params;

    // Update the parameters with the ones from the command line
    params.fresh = params_cli.fresh;
    params.performance_test = params_cli.performance_test;

    return params;
}
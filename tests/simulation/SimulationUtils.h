#pragma once

#include "data/FileLoader.h"
#include "simulation/SimulationParams.h"

const SimulationParams TEST_DEFAULT_PARAMS_GRAVITY(FileLoader::get_input_file_path("empty.xml"), 0.002, 5, 24, 30,
                                                   SimulationParams::DirectSumType{}, std::nullopt, "none", {"Gravitational"}, false, true);

const SimulationParams TEST_DEFAULT_PARAMS_LENNARD_JONES(FileLoader::get_input_file_path("empty.xml"), 0.002, 5, 24, 30,
                                                         SimulationParams::DirectSumType{}, std::nullopt, "none", {"LennardJones"}, false,
                                                         true);

#pragma once
#include "simulation/SimulationParams.h"

const SimulationParams TEST_DEFAULT_PARAMS_GRAVITY("test_only.xml", "", 0.002, 5, 24, 30, SimulationParams::DirectSumType{}, "none",
                                                   {"Gravitational"}, false, true);

const SimulationParams TEST_DEFAULT_PARAMS_LENNARD_JONES("test_only.xml", "", 0.002, 5, 24, 30, SimulationParams::DirectSumType{}, "none",
                                                         {"LennardJones"}, false, true);

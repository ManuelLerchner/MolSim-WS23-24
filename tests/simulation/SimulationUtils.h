#pragma once
#include "simulation/SimulationParams.h"

const SimulationParams TEST_DEFAULT_PARAMS_GRAVITY =
    SimulationParams("test_only", "", 0.002, 5, 24, 30, SimulationParams::DirectSumType{}, "none", {"Gravitational"}, false);

const SimulationParams TEST_DEFAULT_PARAMS_LENNARD_JONES =
    SimulationParams("test_only", "", 0.002, 5, 24, 30, SimulationParams::DirectSumType{}, "none", {"LennardJones"}, false);
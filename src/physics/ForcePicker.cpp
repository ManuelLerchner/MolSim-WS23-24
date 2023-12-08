#include "ForcePicker.h"

#include <numeric>

#include "io/logger/Logger.h"
#include "physics/GravitationalForce.h"
#include "physics/LennardJonesForce.h"

std::map<std::string, std::shared_ptr<ForceSource>> ForcePicker::get_supported_forces() {
    std::map<std::string, std::shared_ptr<ForceSource>> force_names;

    auto lennardjones = std::make_shared<LennardJonesForce>();
    auto gravitational = std::make_shared<GravitationalForce>();

    force_names.insert({std::string(*lennardjones), lennardjones});
    force_names.insert({std::string(*gravitational), gravitational});

    return force_names;
}

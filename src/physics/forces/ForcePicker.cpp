#include "ForcePicker.h"

#include <numeric>

#include "io/logger/Logger.h"
#include "physics/forces/GlobalDownwardsGravity.h"
#include "physics/forces/GravitationalForce.h"
#include "physics/forces/LennardJonesForce.h"

std::map<std::string, std::shared_ptr<ForceSource>> ForcePicker::get_supported_forces() {
    std::map<std::string, std::shared_ptr<ForceSource>> force_names;

    auto lennardjones = std::make_shared<LennardJonesForce>();
    auto gravitational = std::make_shared<GravitationalForce>();
    auto global_downwards_gravity = std::make_shared<GlobalDownwardsGravity>();

    force_names.insert({std::string(*lennardjones), lennardjones});
    force_names.insert({std::string(*gravitational), gravitational});
    force_names.insert({std::string(*global_downwards_gravity), global_downwards_gravity});

    return force_names;
}

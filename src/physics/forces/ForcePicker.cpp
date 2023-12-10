#include "ForcePicker.h"

#include <numeric>

#include "io/logger/Logger.h"
#include "physics/forces/GlobalDownwardsGravity.h"
#include "physics/forces/GravitationalForce.h"
#include "physics/forces/LennardJonesForce.h"

std::set<std::string> ForcePicker::get_supported_forces() {
    std::set<std::string> force_names;

    auto lennardjones = LennardJonesForce();
    auto gravitational = GravitationalForce();
    auto global_downwards_gravity = GlobalDownwardsGravity();

    force_names.insert(std::string(lennardjones));
    force_names.insert(std::string(gravitational));
    force_names.insert(std::string(global_downwards_gravity));

    return force_names;
}

std::unique_ptr<ForceSource> ForcePicker::pick_force(const std::string& force_name) {
    auto supported = get_supported_forces();

    if (!supported.contains(force_name)) {
        auto supported_forces = std::string();
        for (auto& name : supported) {
            supported_forces += name + ", ";
        }

        Logger::logger->error("Invalid force given: {}. Supported forces are: {}", force_name, supported_forces);
        exit(-1);
    }

    if (force_name == std::string(LennardJonesForce())) {
        return std::make_unique<LennardJonesForce>();
    } else if (force_name == std::string(GravitationalForce())) {
        return std::make_unique<GravitationalForce>();
    } else if (force_name == std::string(GlobalDownwardsGravity())) {
        return std::make_unique<GlobalDownwardsGravity>();
    }

    Logger::logger->error("Invalid force given: {}", force_name);
    exit(-1);
}
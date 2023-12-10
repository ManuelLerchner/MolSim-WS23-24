#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

#include "physics/forces/ForceSource.h"

class ForcePicker {
   public:
    static std::set<std::string> get_supported_forces();

    static std::unique_ptr<ForceSource> pick_force(const std::string& force_name);
};

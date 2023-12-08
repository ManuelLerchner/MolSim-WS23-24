#pragma once

#include <map>
#include <memory>
#include <string>

#include "physics/ForceSource.h"

class ForcePicker {
   public:
    static std::map<std::string, std::shared_ptr<ForceSource>> get_supported_forces();
};

#pragma once

#include "exam/types.hpp"

#include <string>
#include <vector>

namespace judge {

enum class RunMode {
    AUTO,
    INTERACTIVE
};

struct Scenario {
    std::string name;
    int maxRounds{100};
    std::vector<exam::EnemyRobot> arrivals;
};

Scenario loadScenario(const std::string& path);

}  // namespace judge

#include "exam/types.hpp"

#include <stdexcept>
#include <string>

namespace exam {

std::string toString(RobotType type) {
    switch (type) {
    case RobotType::HERO:
        return "HERO";
    case RobotType::SENTRY:
        return "SENTRY";
    case RobotType::INFANTRY:
        return "INFANTRY";
    case RobotType::ENGINEER:
        return "ENGINEER";
    }

    throw std::invalid_argument("unknown robot type");
}

RobotType robotTypeFromString(const std::string& text) {
    if (text == "HERO") {
        return RobotType::HERO;
    }
    if (text == "SENTRY") {
        return RobotType::SENTRY;
    }
    if (text == "INFANTRY") {
        return RobotType::INFANTRY;
    }
    if (text == "ENGINEER") {
        return RobotType::ENGINEER;
    }

    throw std::invalid_argument(
        "unknown robot type text: " + text
    );
}

int officialAttackPower(RobotType type) {
    switch (type) {
    case RobotType::HERO:
        return 30;
    case RobotType::SENTRY:
        return 25;
    case RobotType::INFANTRY:
        return 15;
    case RobotType::ENGINEER:
        return 0;
    }

    throw std::invalid_argument("unknown robot type");
}

}  // namespace exam

#include "judge/scenario.hpp"

#include <fstream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

namespace judge {
namespace {

void expectKey(
    std::istream& input,
    const std::string& expected,
    const std::string& errorMessage
) {
    std::string key;
    if (!(input >> key) || key != expected) {
        throw std::runtime_error(errorMessage);
    }
}

void readScenarioName(
    std::istream& input,
    Scenario& scenario
) {
    expectKey(input, "name", "expected: name <scenario-name>");

    if (!(input >> scenario.name) || scenario.name.empty()) {
        throw std::runtime_error("scenario name is empty");
    }
}

void readMaxRounds(
    std::istream& input,
    Scenario& scenario
) {
    expectKey(input, "max_rounds", "expected: max_rounds <positive-number>");

    if (!(input >> scenario.maxRounds) || scenario.maxRounds <= 0) {
        throw std::runtime_error("max_rounds must be positive");
    }
}

int readRobotCount(std::istream& input) {
    expectKey(input, "count", "expected: count <non-negative-number>");

    int count = 0;
    if (!(input >> count) || count < 0) {
        throw std::runtime_error("robot count must be non-negative");
    }

    return count;
}

exam::EnemyRobot readRobot(
    std::istream& input,
    std::set<int>& usedIds
) {
    int id = 0;
    std::string typeText;
    std::string name;
    int hp = 0;
    int distance = 0;

    if (!(input >> id >> typeText >> name >> hp >> distance)) {
        throw std::runtime_error("invalid robot row");
    }

    if (id <= 0) {
        throw std::runtime_error("robot id must be positive");
    }

    if (!usedIds.insert(id).second) {
        throw std::runtime_error("duplicate robot id: " + std::to_string(id));
    }

    if (hp <= 0) {
        throw std::runtime_error("robot hp must be positive");
    }

    if (distance < 0) {
        throw std::runtime_error("robot distance cannot be negative");
    }

    const exam::RobotType type =
        exam::robotTypeFromString(typeText);

    exam::EnemyRobot robot;
    robot.id = id;
    robot.type = type;
    robot.name = name;
    robot.hp = hp;
    robot.distance = distance;
    robot.attackPower = exam::officialAttackPower(type);
    return robot;
}

}  // namespace

Scenario loadScenario(const std::string& path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error(
            "cannot open scenario file: " + path
        );
    }

    Scenario scenario;
    readScenarioName(input, scenario);
    readMaxRounds(input, scenario);

    const int robotCount = readRobotCount(input);
    scenario.arrivals.reserve(static_cast<std::size_t>(robotCount));

    std::set<int> usedIds;
    for (int index = 0; index < robotCount; ++index) {
        scenario.arrivals.push_back(
            readRobot(input, usedIds)
        );
    }

    return scenario;
}

}  // namespace judge

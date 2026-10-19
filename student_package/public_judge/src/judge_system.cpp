#include "judge/judge_system.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace judge {
namespace {

bool isAlive(const exam::EnemyRobot& robot) {
    return robot.hp > 0;
}

}  // namespace

JudgeSystem::JudgeSystem(int argc, char** argv) {
    if (argc < 2) {
        throw std::invalid_argument(
            "usage: sentinel_judge scenario [--interactive] [--verbose]\n"
            "                        [--dump-battlefield]\n"
            "                        [--dump-each-round]\n"
            "                        [--dump-file <path>]"
        );
    }

    parseOptions(argc, argv);
    scenario_ = loadScenario(argv[1]);
    prepareDumpFile();
}

void JudgeSystem::parseOptions(int argc, char** argv) {
    for (int index = 2; index < argc; ++index) {
        const std::string argument = argv[index];

        if (argument == "--interactive") {
            mode_ = RunMode::INTERACTIVE;
        } else if (argument == "--verbose") {
            verbose_ = true;
        } else if (argument == "--dump-battlefield") {
            dumpAtEnd_ = true;
        } else if (argument == "--dump-each-round") {
            dumpEachRound_ = true;
        } else if (argument == "--dump-file") {
            if (index + 1 >= argc) {
                throw std::invalid_argument(
                    "--dump-file needs a path"
                );
            }
            dumpFile_ = argv[++index];
        } else {
            throw std::invalid_argument(
                "unknown option: " + argument
            );
        }
    }
}

void JudgeSystem::prepareDumpFile() {
    if (dumpFile_.empty()) {
        return;
    }

    // 每次运行都从空文件开始，避免和上一次的结果混在一起。
    std::ofstream output(dumpFile_, std::ios::trunc);
    if (!output.is_open()) {
        throw std::runtime_error(
            "cannot open dump file: " + dumpFile_
        );
    }
}

bool JudgeSystem::battleContinues() const {
    if (finished_) {
        return false;
    }

    return currentTime_ < scenario_.maxRounds;
}

bool JudgeSystem::allRobotsRevealed() const {
    return nextArrivalIndex_ >= scenario_.arrivals.size();
}

exam::RadarResult JudgeSystem::readRadar() {
    ++currentTime_;

    exam::RadarResult radar;

    if (nextArrivalIndex_ < scenario_.arrivals.size()) {

        radar.hasNewRobot = true;
        radar.robot = scenario_.arrivals[nextArrivalIndex_];
        activeRobots_.push_back(radar.robot);
        ++nextArrivalIndex_;
    }

 
    if (dumpEachRound_) {
        dumpBattlefield(std::cout);
    }

    if (!dumpFile_.empty()) {
        appendDumpToFile();
    }

    return radar;
}

void JudgeSystem::dumpBattlefield(std::ostream& out) const {
    out << "=== REAL BATTLEFIELD"
        << " round=" << currentTime_
        << " alive=" << countAliveRobots()
        << " published=" << countPublishedRobots()
        << " damage_taken=" << totalDamageTaken_
        << " invalid=" << invalidDecisionCount_
        << " ===\n";

    for (const auto& robot : activeRobots_) {
        out << "id=" << robot.id
            << " type=" << exam::toString(robot.type)
            << " name=" << robot.name
            << " hp=" << robot.hp
            << " distance=" << robot.distance
            << " attack=" << robot.attackPower
            << " alive=" << (isAlive(robot) ? "yes" : "no")
            << '\n';
    }

    out << std::flush;
}

void JudgeSystem::appendDumpToFile() const {
    if (dumpFile_.empty()) {
        return;
    }

    std::ofstream output(dumpFile_, std::ios::app);
    if (!output.is_open()) {
        return;
    }

    dumpBattlefield(output);
}

int JudgeSystem::countPublishedRobots() const {
    return static_cast<int>(activeRobots_.size());
}

exam::EnemyRobot* JudgeSystem::findAliveRobot(int id) {
    for (auto& robot : activeRobots_) {
        if (robot.id == id && isAlive(robot)) {
            return &robot;
        }
    }

    return nullptr;
}

int JudgeSystem::countAliveRobots() const {
    return static_cast<int>(std::count_if(
        activeRobots_.begin(),
        activeRobots_.end(),
        [](const exam::EnemyRobot& robot) {
            return isAlive(robot);
        }
    ));
}

int JudgeSystem::calculateEnemyDamage() const {
    int damage = 0;

    for (const auto& robot : activeRobots_) {
        if (isAlive(robot)) {
            damage += robot.attackPower;
        }
    }

    return damage;
}

int JudgeSystem::calculatePlayerDamage(
    const exam::EnemyRobot& target
) const {
    return std::max(1, 20 - target.distance / 100);
}

void JudgeSystem::resolveRound(int targetId) {
    const int enemyDamage = calculateEnemyDamage();
    int playerDamage = 0;
    int destroyedId = -1;

    exam::EnemyRobot* target = findAliveRobot(targetId);
    if (target == nullptr) {
        ++invalidDecisionCount_;
    } else {
        playerDamage = calculatePlayerDamage(*target);
        target->hp = std::max(0, target->hp - playerDamage);

        if (target->hp == 0) {
            destroyedId = target->id;
        }
    }

    totalDamageTaken_ += enemyDamage;

    if (verbose_) {
        std::cout << "ROUND " << currentTime_
                  << " target=" << targetId
                  << " damage=" << playerDamage
                  << " received=" << enemyDamage
                  << " total=" << totalDamageTaken_;
        if (destroyedId >= 0) {
            std::cout << " destroyed=" << destroyedId;
        }
        std::cout << '\n';
    }

    if (allRobotsRevealed() && countAliveRobots() == 0) {
        finished_ = true;
    }
}

bool JudgeSystem::isInteractive() const {
    return mode_ == RunMode::INTERACTIVE;
}

int JudgeSystem::finish() const {
    if (dumpAtEnd_) {
        dumpBattlefield(std::cout);

        if (!dumpFile_.empty()) {
            appendDumpToFile();
        }
    }

    const bool success =
        allRobotsRevealed() && countAliveRobots() == 0;

    std::cout << "RESULT"
              << " scenario=" << scenario_.name
              << " success=" << success
              << " rounds=" << currentTime_
              << " damage=" << totalDamageTaken_
              << " remaining=" << countAliveRobots()
              << " invalid=" << invalidDecisionCount_
              << '\n';

    return success ? 0 : 1;
}

}  // namespace judge

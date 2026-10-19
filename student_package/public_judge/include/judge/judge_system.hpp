#pragma once

#include "exam/types.hpp"
#include "judge/scenario.hpp"

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

namespace judge {


class JudgeSystem {
public:
    JudgeSystem(int argc, char** argv);

    // 战斗是否继续：还有回合剩余且尚未全灭。
    bool battleContinues() const;


    exam::RadarResult readRadar();


    void resolveRound(int targetId);

    // 是否启用交互模式（命令行 --interactive）。
    bool isInteractive() const;


    int finish() const;

   
    void dumpBattlefield(std::ostream& out) const;

private:
    void parseOptions(int argc, char** argv);
    void prepareDumpFile();
    void appendDumpToFile() const;

    exam::EnemyRobot* findAliveRobot(int id);
    int countAliveRobots() const;
    int countPublishedRobots() const;
    int calculateEnemyDamage() const;
    int calculatePlayerDamage(
        const exam::EnemyRobot& target
    ) const;
    bool allRobotsRevealed() const;

    Scenario scenario_;
    RunMode mode_{RunMode::AUTO};
    bool verbose_{false};

    bool dumpAtEnd_{false};
    bool dumpEachRound_{false};
    std::string dumpFile_;

    std::vector<exam::EnemyRobot> activeRobots_;
    std::size_t nextArrivalIndex_{0};
    int currentTime_{0};
    long long totalDamageTaken_{0};
    int invalidDecisionCount_{0};
    bool finished_{false};
};

}  // namespace judge

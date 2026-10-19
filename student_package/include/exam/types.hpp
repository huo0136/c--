#pragma once

#include <string>

namespace exam {

// 敌方机器人类型。
enum class RobotType {
    HERO,
    SENTRY,
    INFANTRY,
    ENGINEER
};

// 雷达公开的一台机器人数据。
//
// hp       ：雷达公开时的血量，等于该机器人的满血血量。
//            公开之后血量不会再由雷达刷新，需要学生自己维护。
// distance ：固定距离，公开后不再变化。
// attackPower：由类型决定；工程机器人为 0。
struct EnemyRobot {
    int id{};
    RobotType type{};
    std::string name;
    int hp{};
    int distance{};
    int attackPower{};
};

// 雷达每回合的读取结果。
//
// hasNewRobot == true  ：本回合公开了机器人，数据在 robot 中。
// hasNewRobot == false ：已经没有未公开机器人，robot 为默认值，
//                        学生应当忽略 robot 字段。
struct RadarResult {
    bool hasNewRobot{};
    EnemyRobot robot{};
};

std::string toString(RobotType type);
RobotType robotTypeFromString(const std::string& text);
int officialAttackPower(RobotType type);

}  // namespace exam

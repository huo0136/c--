#pragma once

#include "exam/types.hpp"
#include <map>
#include <algorithm>
#include <vector>
#include <string>
class RobotManager;

class Tactics//策略的基类 
{
public:
    virtual ~Tactics() = default;//为了基类指针delete子类对象时能正确析构子类
    virtual int choose(const std::vector<exam::EnemyRobot>& r) const = 0;//纯虚函数，实现多态
    virtual std::string name() const = 0;
    //const 在成员函数前面，表示返回值不可改；const在成员函数后面，表示该函数不会改成员变量
};

// 策略 1：威胁度 = 攻击力 / 击杀所需回合数
//Damage = std::max(1, 20 - target.distance / 100);
class MaxThreatTactics : public Tactics 
{
public:
    int choose(const std::vector<exam::EnemyRobot>& r) const override; 
    std::string name() const override { return "MAX_THREAT"; }
};

// 策略 2：低血量优先（血量越小，分数越高）
class LowHpTactics : public Tactics 
{
public:
    int choose(const std::vector<exam::EnemyRobot>& r) const override;
    std::string name() const override { return "LOW_HP"; }
};

// 策略 3：最近目标优先（距离越小，分数越高）
class NearestTactics : public Tactics 
{
public:
    int choose(const std::vector<exam::EnemyRobot>& r) const override ;
    std::string name() const override { return "NEAREST"; }
};

class SentinelStrategy {
public:
    std::vector<exam::EnemyRobot> Alive(const std::vector<exam::EnemyRobot>& r);
    int chooseTarget(RobotManager& manager);
};

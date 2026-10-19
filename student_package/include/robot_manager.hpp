#pragma once
#include "strategy.hpp"
#include "exam/types.hpp"
#include <vector>
#include <memory>

class RobotManager 
{
public:
 
    void update(const exam::RadarResult& radar);
    void menu();

    //对strategy的外部接口
    void ApplyAttack(int id);
    const Tactics& getTactics() const { return *tactics_; }
    void setTactics(std::unique_ptr<Tactics> t) { tactics_ = std::move(t); }
    const std::vector<exam::EnemyRobot>& GetEnemyRobots() const;

private:

    //内部菜单调用
    bool IsAlive(const exam::EnemyRobot& r);
    void ShowMenu();
    void PrintAllRobotsStatus();
    void ShowRobotById(const int& id);
    void SortRobotByDistance();
    void SwitchTacticsMenu();
    void PrintAliveRobots();

    int CurrentRound=0;
    std::vector<exam::EnemyRobot> EnemyRobots;
    bool menuSkipped=false;
    int skipRounds=0;    // 还要跳过多少回合菜单

    //智能指针，指向策略类
    std::unique_ptr<Tactics> tactics_ = std::make_unique<MaxThreatTactics>();
    //unique_ptr是指指向的内容只能由它来指向，不能被别的指针指向
};

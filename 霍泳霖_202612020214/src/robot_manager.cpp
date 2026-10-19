#include "robot_manager.hpp"
#include "strategy.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
void RobotManager::update(const exam::RadarResult& radar) {
    CurrentRound++;
    if(radar.hasNewRobot==true) 
    {
        exam::EnemyRobot r;
        r.attackPower=radar.robot.attackPower;
        r.distance=radar.robot.distance;
        r.name=radar.robot.name;
        r.id=radar.robot.id;
        r.type=radar.robot.type;
        r.hp=radar.robot.hp;
        EnemyRobots.push_back(r);
    }
}

bool RobotManager::IsAlive(const exam::EnemyRobot& r)
{
    if(r.hp==0) return false;
    return true;
}

void RobotManager::ShowMenu()
{
    std::cout <<"  ----------------------------------\n";
    std::cout << "  s          Show all robots' status\n";
    std::cout << "  a          Show alive robots' status\n";
    std::cout << "  q <id>     Query a robot by ID\n";
    std::cout << "  d          Show robots sorted by distance\n";
    std::cout << "  r          Show current round\n";
    std::cout << "  m          Switch tactics mode\n";
    std::cout << "  j <n>      Skip next n rounds' menus (including this one)\n";
    std::cout << "  p          Skip this round (continue battle)\n";
    std::cout << "  e          Exit the menu\n";
    std::cout << "  ----------------------------------\n";
}

void RobotManager::PrintAllRobotsStatus()
{
    if(EnemyRobots.empty())
    {
        std::cout << "  [No robot information available yet]\n";
        return;
    }
    std::cout << "\n  --- All robots (" << EnemyRobots.size() << " total) ---\n";
    std::cout << "  " << std::left
              << std::setw(6)  << "ID"
              << std::setw(12) << "TYPE"
              << std::setw(16) << "NAME"
              << std::setw(8)  << "HP"
              << std::setw(10) << "DIST"
              << std::setw(10) << "ATK"
              << "STATE\n";
    std::cout << "  " << std::string(70, '-') << '\n';
    
    for(auto& robot:EnemyRobots)
    {
        std::cout << "  " << std::left
                  << std::setw(6)  << robot.id
                  << std::setw(12) << exam::toString(robot.type)
                  << std::setw(16) << robot.name
                  << std::setw(8)  << robot.hp
                  << std::setw(10) << robot.distance
                  << std::setw(10) << robot.attackPower
                  << (robot.hp > 0 ? "ALIVE" : "DESTROYED") << '\n';
    }
}

void RobotManager::ShowRobotById(const int& id)
{
    for(auto& robot:EnemyRobots)
    {
        if(robot.id==id)
        {
            std::cout << "\n  --- Robot ID=" << id << " ---\n";
            std::cout << "    Type        : " << exam::toString(robot.type) << '\n';
            std::cout << "    Name        : " << robot.name << '\n';
            std::cout << "    Current HP  : " << robot.hp << '\n';
            std::cout << "    Distance    : " << robot.distance << '\n';
            std::cout << "    Attack      : " << robot.attackPower << '\n';
            std::cout << "    State       : " << (robot.hp > 0 ? "ALIVE" : "DESTROYED") << '\n';
            std::cout << "    Our Damage  : " << std::max(1, 20 - robot.distance / 100) << '\n';
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "  No such ID here!\n";
}

void RobotManager::SortRobotByDistance()
{
   std::vector<exam::EnemyRobot> sorts = EnemyRobots;   // 复制一份
   std::sort(sorts.begin(), sorts.end(),
        [](const exam::EnemyRobot& a, const exam::EnemyRobot& b) {
            return a.distance < b.distance;
        }); 
    std::cout << "\n  --- All robots (" << EnemyRobots.size() << " total,sorted by distance) ---\n";
    std::cout << "  " << std::left
              << std::setw(10) << "DIST"
              << std::setw(6)  << "ID"
              << std::setw(12) << "TYPE"
              << std::setw(16) << "NAME"
              << std::setw(8)  << "HP"
              << std::setw(10) << "ATK"
              << "STATE\n";
    std::cout << "  " << std::string(70, '-') << '\n';
    
    for(auto& robot:sorts)
    {
        std::cout << "  " << std::left
                  << std::setw(10) << robot.distance
                  << std::setw(6)  << robot.id
                  << std::setw(12) << exam::toString(robot.type)
                  << std::setw(16) << robot.name
                  << std::setw(8)  << robot.hp
                  << std::setw(10) << robot.attackPower
                  << (robot.hp > 0 ? "ALIVE" : "DESTROYED") << '\n';
    }
}

void RobotManager::SwitchTacticsMenu()
{
    std::cout << "  Current tactics: " << getTactics().name() << "\n";
    std::cout << "  1. MAX_THREAT\n";
    std::cout << "  2. LOW_HP\n";
    std::cout << "  3. NEAREST\n";
    std::cout << "  Select: ";
    std::string sel;
    std::getline(std::cin, sel);
    if (sel == "1")
    {
        setTactics(std::make_unique<MaxThreatTactics>());
        std::cout << "  Tactics switched to MAX_THREAT\n";
    }
    else if (sel == "2") 
    {
        setTactics(std::make_unique<LowHpTactics>());
        std::cout << "  Tactics switched to LOW_HP\n";
    } 
    else if (sel == "3") 
    {
        setTactics(std::make_unique<NearestTactics>());
        std::cout << "  Tactics switched to NEAREST\n";
    } 
    else 
    {
        std::cout << "  [Invalid selection]\n";
    }
}

void RobotManager::PrintAliveRobots()
{
    std::vector<exam::EnemyRobot> alive;
    for(auto& i:EnemyRobots)
    {
        if(i.hp>0) alive.push_back(i);
    }
    if(alive.empty())
    {
        std::cout << "  [No alive robot information available yet]\n";
        return;
    }
    std::cout << "\n  --- All alive robots (" << alive.size() << " total) ---\n";
    std::cout << "  " << std::left
              << std::setw(6)  << "ID"
              << std::setw(12) << "TYPE"
              << std::setw(16) << "NAME"
              << std::setw(8)  << "HP"
              << std::setw(10) << "DIST"
              << std::setw(10) << "ATK"
              << "STATE\n";
    std::cout << "  " << std::string(70, '-') << '\n';
    
    for(auto& robot:alive)
    {
        std::cout << "  " << std::left
                  << std::setw(6)  << robot.id
                  << std::setw(12) << exam::toString(robot.type)
                  << std::setw(16) << robot.name
                  << std::setw(8)  << robot.hp
                  << std::setw(10) << robot.distance
                  << std::setw(10) << robot.attackPower
                  << "ALIVE" << '\n';
    }
}

void RobotManager::menu() 
{
    if(menuSkipped) return;
    if (skipRounds>0) 
    {
        skipRounds--;
        return;
    }
    std::cout << "\n========== Round "<<CurrentRound<<" Interactive Menu ==========\n";
    while(true)
    {
        ShowMenu();
        std::cout<<"  Enter your choice>> ";
        char choice; 
        std::cin>>choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        switch(choice)
        {
            case 's':
            case 'S':
            {
                PrintAllRobotsStatus();
                break;
            }
            case 'a':
            case 'A':
            {
                PrintAliveRobots();
                break;
            }
            case 'q':
            case 'Q':
            {
                std::cout << "  Enter the ID to query: ";
                std::string idStr;
                if (!std::getline(std::cin, idStr)) {
                    break;
                }
                try {
                    ShowRobotById(std::stoi(idStr));
                } catch (...) {
                    std::cout << "  [Invalid ID format]\n";
                }
                break;
            }
            case 'd':
            case 'D':
            {
                SortRobotByDistance();
                break;
            }
            case 'r':
            case 'R':
            {
                std::cout <<"  Current round is "<<CurrentRound<<std::endl;
                break;
            }
            case 'm':
            case 'M':
            {
                SwitchTacticsMenu();
                break;
            }
            case 'j':
            case 'J':
            {
                std::cout << "  How many rounds to skip (including this one)? \n  ";
                std::string nStr;
                std::getline(std::cin, nStr);
                int n=0;
                try 
                {
                    n=std::stoi(nStr);
                } 
                catch (...) 
                {
                    std::cout << "  [Invalid number]\n";
                    break;
                }

                if(n<=0) 
                {
                    std::cout << "  [Number must be positive]\n";
                    break;
                }

                skipRounds=n-1;   // 本回合算一次，后续再跳 n-1 回合
                std::cout << "  Skipping " << n << " round(s) of menus (including this one).\n";
                return;                // 本回合也跳过（直接进战斗）
            }
            case 'p':
            case 'P':
            {
                std::cout<<"  This round has been skipped!"<<std::endl;
                return;
            }
            case 'e':
            case 'E':
            {
                menuSkipped=true;
                return;
            }
            default:
            {
                std::cout <<"Invalid input, please try again"<<std::endl;
                break;
            }
        }
    }
    
}

const std::vector<exam::EnemyRobot>& RobotManager::GetEnemyRobots() const
{
    return EnemyRobots;
}

void RobotManager::ApplyAttack(int id) 
{
    for (auto& robot : EnemyRobots) 
    {
        if (robot.id == id && robot.hp > 0) 
        {
            int dmg = std::max(1, 20 - robot.distance / 100);
            robot.hp = std::max(0, robot.hp - dmg);
            return;
        }
    }
}
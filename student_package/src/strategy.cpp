#include "strategy.hpp"
#include "robot_manager.hpp"
#include <algorithm>
#include <map>
#include <limits>
#include <numeric>

//贪心，威胁度：攻击力/击败所需回合数
int MaxThreatTactics::choose(const std::vector<exam::EnemyRobot>& r) const
{
        int BestID=-1;
        double BestScore=-1e18;
        for(auto& i:r)
        {
            int dmg = std::max(1, 20 - i.distance / 100);
            int rounds = (i.hp + dmg - 1) / dmg;
            double score=double(i.attackPower)/rounds;
            if(score>BestScore)
            {
                BestID=i.id;BestScore=score;
            }
        }
        return BestID;
}

//最低血量优先
int LowHpTactics::choose(const std::vector<exam::EnemyRobot>& r) const
{
        int BestID=-1;
        double BestScore=-1e18;
        for(auto& i:r)
        {
            double score=-i.hp;
            if(score>BestScore)
            {
                BestID=i.id;BestScore=score;
            }
        }    
        return BestID;
}

//最近目标优先
int NearestTactics::choose(const std::vector<exam::EnemyRobot>& r) const
{
    int BestID=-1;
    double BestScore=-1e18;
    for(auto& i:r)
    {
        double score=-i.distance;
        if(score>BestScore)
        {
            BestID=i.id;BestScore=score;
        }
    }    
    return BestID;    
}

std::vector<exam::EnemyRobot> SentinelStrategy::Alive(const std::vector<exam::EnemyRobot>& r)
{
    std::vector<exam::EnemyRobot> alive;
    for(auto& i:r)
    {
        if(i.hp>0) alive.push_back(i);
    }
    return alive;
}

int SentinelStrategy::chooseTarget(RobotManager& manager) 
{
    auto robots=manager.GetEnemyRobots();
    auto alive=Alive(robots);
    if(alive.empty()) return -1;
    const Tactics& t = manager.getTactics();
    int target=t.choose(alive);
    manager.ApplyAttack(target);
    return target;
}


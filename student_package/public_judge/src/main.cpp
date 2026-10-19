#include "judge/judge_system.hpp"
#include "robot_manager.hpp"
#include "strategy.hpp"

int main(int argc, char** argv) {
    // 裁判系统：读取雷达测试文件，并在内部维护真实战场数据
    judge::JudgeSystem judge(argc, argv);

    // 由你设计和实现的两个类
    RobotManager manager;
    SentinelStrategy strategy;

    // 战场每一个回合执行一次循环。
    while (judge.battleContinues()) {


        // 雷达公布数据，每回合最多公布一台机器人
        //
        // 返回值 exam::RadarResult：
        //   radar.hasNewRobot == true
        //       本回合公开了机器人，数据在 radar.robot 中
        //   radar.hasNewRobot == false
        //       已经没有未公开机器人，radar.robot 为默认值，应当忽略
        const exam::RadarResult radar = judge.readRadar();



        // 你需要把雷达数据并入自己维护的战场模型。
        manager.update(radar);

        // 交互模式下（--interactive）：进入你设计的终端菜单，
        if (judge.isInteractive()) {
            manager.menu();
        }



        // 你需要根据自己的战场模型选择本回合攻击目标。
        // 返回该机器人 id；没有可攻击目标时返回 -1
        const int targetId =
            strategy.chooseTarget(manager);



        // 裁判按返回值更新真实战场数据维护战场
        judge.resolveRound(targetId);
    }



    // 裁判结束战场，给出算法部分考核最终得分
    return judge.finish();
}

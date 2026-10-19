# 湖南大学 RoboMaster 跃鹿战队算法组培训一阶段项目考核

湖南大学 RoboMaster 跃鹿战队算法组培训一阶段项目考核题目，内容与评分细则

## 一、题目

湖南大学 RoboMaster 跃鹿战队的哨兵机器人正在执行基地防守任务，请你使用 **C++** 为其战术分析系统**进行补全**，根据雷达机器人每回合提供的信息对战场进行记录并完成对哨兵的火力调度，使哨兵在敌方全部被击毁前**受到的累计伤害尽可能少**。



## 二、战场规则

**战场采用回合制**；

### 1. 回合流程

每回合顺序执行：

1. 雷达机器人公开一台尚未发现的敌方机器人；
2. 所有被雷达公开过且存活的敌方机器人对我方哨兵进行一次攻击；
3. 考生把雷达数据并入自己维护的战场模型`manager`；
4. 交互模式下进入考生设计的菜单；
5. 考生根据自己的模型`manager`返回`strategy`攻击的目标 `id`，裁判检查合法性；
6. 结算我方攻击；
7. 记录结果，进入下一回合。

胜负条件：

```text
所有敌方机器人被击毁        ->  成功
达到最大回合数仍未全灭      ->  失败
```

根据上述流程，**本回合被你击毁的英雄、哨兵或步兵仍然会先手完成本回合攻击，从下一回合开始不再攻击**；

你也可以阅读裁判系统的`main`函数`student_package/public_judge/src/main.cpp`来了解流程

### 2. 雷达机器人

- 每一回合开始时发现一台未被发现敌方机器人，直到无未被发现的敌方机器人；
- 在发现敌方机器人时公布一次此敌方机器人的详细数据 （数据内容详见下文结构体`EnemyRobot`）；

### 3. 敌方机器人

| 类型 | 枚举值 | 攻击力 |
|---|---|---:|
| 英雄 | `HERO` | 30 |
| 哨兵 | `SENTRY` | 25 |
| 步兵 | `INFANTRY` | 15 |
| 工程 | `ENGINEER` | 0 |

- 当敌方机器人被雷达发现且存活时，每一回合开始时对我方哨兵造成攻击力等量的伤害；
- 可能同时出现相同类型的多台敌方机器人；

你需要控制哨兵击毁敌方全部机器人。

### 4. 我方哨兵

- 每一回合造成伤害基础数值为20，伤害随距离衰减，每回合攻击一台敌方机器人；
- 生命值无限，只统计累计受到的伤害；

我方伤害距离衰减公式：

```cpp
Damage = std::max(1, 20 - target.distance / 100);
```

其中 `/` 使用 C++ 整数除法，例如：

| 距离 | 每回合伤害 |
|---:|---:|
| 0～99 | 20 |
| 100～199 | 19 |
| 500～599 | 15 |
| 900～999 | 11 |
| 大于等于 1900 | 1 |



## 三、裁判系统

**除了**下面内容外的代码外的代码**均为**裁判系统

```text
student_package/
├── include/
│   ├── robot_manager.hpp
│   └── strategy.hpp
└── src/
    ├── robot_manager.cpp
    └── strategy.cpp
```

### 1. 裁判

- 提供 `main()`函数、雷达数据读取、同时维护真实战场状态与运行。

- 对**非法目标**发起攻击时，裁判会记为一次**非法决策**（`invalid`）。该回合我方伤害为 0，但敌方伤害照常结算。
- 提供最终运行结果。

考生**不得尝试修改裁判系统、测试数据、伤害公式和评分程序**。

### 2. 数据结构

裁判提供固定头文件，可以阅读，不能修改：

```cpp
#pragma once

#include <string>

enum class RobotType {
    HERO,
    SENTRY,
    INFANTRY,
    ENGINEER
};

struct EnemyRobot {
    int id;
    RobotType type;
    std::string name;
    int hp;            // 雷达公开时的血量，等于满血
    int distance;      // 固定距离，公开后不再变化
    int attackPower;   // 由类型决定
};

struct RadarResult {
    bool hasNewRobot;
    EnemyRobot robot;
};
```

- 雷达每回合公开一台机器人后，**不再提供其信息**；
- `hp` 只是公开时的血量，雷达之后不会再刷新；
- `distance` 公开后固定不变；
- `RadarResult::hasNewRobot == false` 表示没有更多未公开机器人，此时应忽略 `robot` 字段。

### 3. 交互模式

命令行添加 `--interactive` 后，裁判`main()` 每回合调用一次考生设计的 `RobotManager::menu()`，自动模式不调用 `menu()`，但战斗逻辑完全相同，因此两种模式的策略结果必须一致。

## 四、你需要实现

**只有三个考生需要完成的公有函数：**

```cpp
void RobotManager::update(const exam::RadarResult& radar);
void RobotManager::menu();
int SentinelStrategy::chooseTarget(RobotManager& manager);
```

其余类内成员函数、私有数据和算法考生可自由发挥；

可以在不修改`CMakelists`的情况下添加`#include`；

### RobotManager类

```cpp
class RobotManager {
public:
    // 把雷达数据并入自己维护的战场模型
    void update(const exam::RadarResult& radar);

    // 交互（菜单）入口：main() 在 --interactive 时每回合调用一次
    void menu();
    //   menu设计至少包括
    //   输入        输出
    //   s          显示自己维护的全部机器人当前的状态（即当前维护struct EnemyRobot的全部内容）
    //   q <id>     按 ID 查询机器人状态
    //   d          按距离排序输出敌方机器人


    
};
```

实现要求：

- 维护自己的战场模型；

- `update()` 把雷达数据并入自己的模型；
- `radar.hasNewRobot == false` 时不增加新机器人；
- 推算并维护每台敌方机器人的剩余血量；
- 判断哪些机器人已经被击毁；
- 正确处理还没有任何机器人的情况；
- 自主设计`menu()` 菜单，至少具备输入输出功能，能为考官显示自己维护的战场模型，查询战场上各个机器人的状态；
- 为 `strategy`提供数据；

### SentinelStrategy类

```cpp
class SentinelStrategy {
public:
    // 裁判每回合调用一次chooseTarget
    // 输入：manager —— 考生自己维护的战场模型，
    // 输出：本回合要攻击的机器人 ID；没有可攻击目标时返回 -1
    int chooseTarget(RobotManager& manager);
};
```

要求：

- 从自己维护的模型里选择你要击打的仍然存活的目标，返回它的 `id`；

- 没有合法目标时返回 `-1`；

- 返回目标之后，把自己本回合的结果写回模型`manager`，更新目标血量；

  

## 五、编译与运行

以下命令在 **Windows** 上执行，终端用 PowerShell 或 VS Code 的集成终端，工作目录为解压出来的 `student_package` 文件夹。

### 1. 编译

```
cmake -S . -B build
cmake --build build --config Release
```

生成

```
build\Release\sentinel_demo.exe
```

### 若编译失败，尝试以下步骤

```
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build --config Release
```

生成

```
build\sentinel_demo.exe
```



### 2. 运行

```
.\build\Release\sentinel_demo.exe data\public\tutorial.txt
```

如果用的是 MinGW 或 Ninja 生成器，产物在 `build\sentinel_demo.exe`，把后面命令里的 `Release\` 去掉即可，具体看你的exe生成在哪里

在后面加后缀可以输出裁判系统内的内容：

| 后缀                   | 作用                                             |
| ---------------------- | ------------------------------------------------ |
| `--verbose`            | 每回合输出攻击目标和受到的伤害                   |
| `--interactive`        | 打开你自己设计的菜单                             |
| `--dump-each-round`    | 每回合输出裁判维护的真实战场，用来核对自己的模型 |
| `--dump-file real.txt` | 把真实战场写入文件，方便逐回合对比               |

例如

```
.\build\Release\sentinel_demo.exe data\public\tutorial.txt --verbose
```

### 3. 第一次运行应该看到什么

**刚解压、代码还没写时**：

```
RESULT scenario=tutorial success=0 rounds=100 damage=8295 remaining=6 invalid=100
```

是正常现象。模板里的 `chooseTarget()` 固定返回 `-1`，等于不攻击任何目标：

```
invalid=100    100 个回合都返回了非法目标
damage=8295    敌人一直在打你
remaining=6    6 台敌人一台都没死
rounds=100     撞到回合上限
```

加 `--verbose` 看每回合：

```
ROUND 1 target=-1 damage=0 received=15 total=15
ROUND 2 target=-1 damage=0 received=15 total=30
ROUND 3 target=-1 damage=0 received=45 total=75
```

`target=-1` 和 `damage=0` 说明这一回合没有攻击任何目标。

**实现完成后**，同一份数据应该变成：

```
RESULT scenario=tutorial success=1 rounds=28 damage=840 remaining=0 invalid=0
```

```
ROUND 1 target=101 damage=19 received=15 total=15
ROUND 2 target=101 damage=19 received=15 total=30
ROUND 3 target=101 damage=19 received=45 total=75 destroyed=101
```

两者对比，就是你要达到的效果：

| 字段        | 空实现 | 实现完成 |
| ----------- | -----: | -------: |
| `success`   |      0 |        1 |
| `rounds`    |    100 |       28 |
| `damage`    |   8295 |      840 |
| `remaining` |      6 |        0 |
| `invalid`   |    100 |        0 |

### 4. RESULT 字段说明

```
RESULT scenario=tutorial success=1 rounds=28 damage=840 remaining=0 invalid=0
```

| 字段        | 含义                                         |
| ----------- | -------------------------------------------- |
| `scenario`  | 测试数据名称                                 |
| `success`   | 是否击毁全部敌方机器人（`1` 成功，`0` 失败） |
| `rounds`    | 总回合数                                     |
| `damage`    | 累计受到的伤害，**越小越好**                 |
| `remaining` | 剩余敌人数                                   |
| `invalid`   | 非法决策次数，**必须为 0**                   |

### 5. 核对自己的战场模型

`--dump-each-round` 输出的是裁判维护的真实战场：

```
.\build\Release\sentinel_demo.exe data\public\tutorial.txt --dump-each-round
```

```
=== REAL BATTLEFIELD round=3 alive=3 published=3 damage_taken=30 invalid=0 ===
id=101 type=INFANTRY name=infantry_a hp=17 distance=100 attack=15 alive=yes
id=205 type=ENGINEER name=engineer_a hp=70 distance=300 attack=0 alive=yes
id=309 type=HERO name=hero_a hp=110 distance=200 attack=30 alive=yes
```

它输出在雷达公布之后、`manager.update(radar)` 之前，对应你本回合应该维护出来的战场状态：

```
真实   id=101 hp=17 alive=yes
你的   id=101 hp=17 alive=yes   ->  模型正确

真实   id=101 hp=0  alive=no
你的   id=101 hp=2  alive=yes   ->  血量推算有误
```

可通过裁判的真实维护战场对比你维护的战场，检查代码正确性

提交的策略代码只能依赖雷达数据和自己维护的模型，**不得读取真实战场数据**



## 六、提交要求

提交目录使用「姓名_学号」命名：

```text
姓名_学号/
├── include/
│   ├── robot_manager.hpp
│   └── strategy.hpp
└── src/
    ├── robot_manager.cpp
    └── strategy.cpp
```

不要上交其他内容，不要修改文件名称。



## 七、验收与评分

考核包括裁判系统编译测试、代码审查、交互演示、策略排名、面试和附加任务，
评分方式见下表。评估过程中会使用两份不同的测试数据分别运行一次。

### 1. 评分表（总分 100）

| 评价部分 | 分值 |
|---|---:|
| 基础功能 | 20 |
| 代码审查 | 15 |
| 交互menu演示 | 20 |
| 策略strategy排名 | 20 |
| 面试 | 20 |
| 附加部分 | 5 |

**基础功能**

| 项目 | 分值 |
|---|---:|
| 编译通过 | 5 |
| 三个必做接口完成 | 5 |
| 两次测试战斗可以完成（`success=1`） | 5 |
| 两次测试无非法决策（`invalid=0`） | 5 |

**代码审查**

| 项目 | 分值 |
|---|---:|
| 类设计和封装 | 5 |
| 代码模块化和代码可读性 | 5 |
| STL使用 | 5 |

**交互演示**

| 项目 | 分值 |
|---|---:|
| 可正常显示，输入、输出不影响流程 | 5 |
| 可显示自己维护的全部机器人 | 5 |
| 可按 ID 查询机器人状态 | 5 |
| 可按距离排序敌方机器人 | 5 |

**策略排名**

基础功能中出现战斗无法完成（`success=0`）情况的，不参与此排名，此项计0分；

策略排名得分细则如下：

用不同文件共测试两次

以按顺序依次击毁雷达机器人公布的机器人的策略为最差策略，此策略计0分；此策略哨兵受到的伤害设为`x`;

以排名最高者受到的最小伤害的策略为最优策略，此策略计10分；此策略哨兵受到的伤害设为`y`;

其他策略哨兵受到的伤害设为`z`;

其他策略计分公式为 `10.0*(x-z)/(x-y)`；负数计0分；

两次测试分数相加为最终策略排名。

**面试**

面试内容主要围绕你的代码和部分RM通识。

**附加任务**

| 任务 | 要求 | 分值 |
|---|---|---:|
| 多种战术模式 | 可以从`menu`中修改实时策略实现低血量优先、最近目标优先等模式，并支持切换 | 3 |
| 战斗回放 | 保存每回合历史记录并生成文件 | 2 |

### 2. 扣分项

下列情况按由轻到重的顺序排列，扣分随情节严重程度逐级增加；不同问题和重复问题累计扣分，上不封顶。情节特别严重者可直接取消成绩，并按照战队规定处理。

- 编译不过；
- 程序崩溃、超时或产生大量异常输出；
- 尝试读取测试文件称或未来机器人信息；
- 尝试读取或修改裁判系统、测试数据、伤害公式或评分脚本；
- 明显抄袭雷同；
- 其他任何违反战队规定事务



## **最终解释权归湖南大学 RoboMaster 跃鹿战队算法组所有**

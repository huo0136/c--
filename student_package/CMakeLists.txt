cmake_minimum_required(VERSION 3.16)
project(rm_sentinel_v13_student LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(sentinel_demo
    public_judge/src/main.cpp
    public_judge/src/types.cpp
    public_judge/src/scenario.cpp
    public_judge/src/judge_system.cpp
    src/robot_manager.cpp
    src/strategy.cpp
)

target_include_directories(sentinel_demo PRIVATE
    include
    public_judge/include
)

if(MSVC)
    target_compile_options(sentinel_demo PRIVATE /W4)
else()
    target_compile_options(sentinel_demo PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

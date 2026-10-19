cmake_minimum_required(VERSION 3.16)

project(Test1Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# test1是你得到的可执行文件的名字,test1.cpp是你将要编译的cpp程序
add_executable(test1 main.cpp root.cpp reader.cpp readermenu.cpp rootmenu.cpp)
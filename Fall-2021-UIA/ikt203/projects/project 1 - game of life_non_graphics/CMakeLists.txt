cmake_minimum_required(VERSION 3.20)
project(project_1___game_of_life C)
#project(project_1___game_of_life)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 14)

add_executable(project_1___game_of_life main.c patterns.h)
#add_executable(project_1___game_of_life main.cpp)
#target_link_libraries(project_1___game_of_life "C:\\mingw64\\lib\\libbgi.a")
#include_directories(C:\\mingw64\\include)
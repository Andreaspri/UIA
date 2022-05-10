cmake_minimum_required(VERSION 3.20)
project(project_4___maze_navigation)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_4___maze_navigation main.cpp includes/library.h includes/library.cpp includes/queue.cpp includes/queue.h includes/queue_wave_front.cpp includes/queue_wave_front.h includes/Stack_returnpath.h includes/Stack_returnpath.cpp includes/godtnavn.cpp includes/godtnavn.h includes/bestanavnet.h)

target_link_libraries(project_4___maze_navigation sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

include_directories(includes assets)

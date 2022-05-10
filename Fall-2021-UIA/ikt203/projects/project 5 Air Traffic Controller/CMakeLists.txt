cmake_minimum_required(VERSION 3.20)
project(project_5_Air_Traffic_Controller)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_5_Air_Traffic_Controller main.cpp includes/queue.cpp includes/queue.h includes/linked_list.cpp includes/linked_list.h includes/Graphics.cpp includes/Graphics.h includes/aircraft.cpp includes/aircraft.h includes/gift_wrap_algorithm.cpp includes/gift_wrap_algorithm.h)


target_link_libraries(project_5_Air_Traffic_Controller sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

include_directories(includes assets)
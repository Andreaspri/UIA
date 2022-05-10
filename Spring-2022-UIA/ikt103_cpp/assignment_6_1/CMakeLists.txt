cmake_minimum_required(VERSION 3.21)
project(assignment_6_1)

set(CMAKE_CXX_STANDARD 14)







add_executable(assignment_6_1 main.cpp Client.cpp Client.h)
find_package(cpprestsdk REQUIRED)
target_link_libraries(assignment_6_1 PRIVATE cpprestsdk::cpprest)

if (UNIX)
    target_link_libraries(assignment_6_1 PRIVATE crypto)
endif (UNIX)
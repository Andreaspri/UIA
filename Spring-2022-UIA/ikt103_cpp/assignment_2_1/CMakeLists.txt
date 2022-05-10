cmake_minimum_required(VERSION 3.21)
project(assignment_2_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment_2_1 main.cpp Model/Student.cpp Model/Student.h Model/Test.cpp Model/Test.h Model/TestResult.cpp Model/TestResult.h Controller/MainController.cpp Controller/MainController.h Model/Database.cpp Model/Database.h)

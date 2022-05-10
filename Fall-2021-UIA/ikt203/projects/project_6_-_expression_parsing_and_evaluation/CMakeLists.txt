cmake_minimum_required(VERSION 3.20)
project(project_6___expression_parsing_and_evaluation)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_6___expression_parsing_and_evaluation main.cpp laae/laae.cpp laae/laae.h myString/myString.h myString/myString.cpp parsetree/parsetree.cpp parsetree/parsetree.cpp parsetree/parsetree.h)

include_directories(laae myString parsetree)

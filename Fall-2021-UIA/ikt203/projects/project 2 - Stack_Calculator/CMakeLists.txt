cmake_minimum_required(VERSION 3.20)
project(Stack_Calculator C)

set(CMAKE_C_STANDARD 99)

add_executable(project_2___Stack_Calculator main.c include/stack.h include/stack.c include/myString.c include/myString.h)

include_directories(include)

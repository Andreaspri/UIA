cmake_minimum_required(VERSION 3.20)
project(slett)

set(CMAKE_CXX_STANDARD 14)

add_executable(slett winbgi.cpp main.cpp patterns.h ../../../../../mingw64/lib/gcc/x86_64-w64-mingw32/7.3.0/include/graphics.h)
cmake_minimum_required(VERSION 3.21)
project(assignment_5_1)

set(CMAKE_CXX_STANDARD 14)

# SQLite library
add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

# SQLiteCpp library
add_library(sqlitecpp
        sqlitecpp/src/Backup.cpp
        sqlitecpp/src/Column.cpp
        sqlitecpp/src/Database.cpp
        sqlitecpp/src/Exception.cpp
        sqlitecpp/src/Statement.cpp
        sqlitecpp/src/Transaction.cpp
        )

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

# Program executable
add_executable(assignment_5_1 main.cpp Database.cpp Database.h)
target_link_libraries(assignment_5_1 sqlite3 sqlitecpp)

if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)
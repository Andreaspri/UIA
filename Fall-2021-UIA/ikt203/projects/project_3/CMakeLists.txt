cmake_minimum_required(VERSION 3.20)
project(project_3)

set(CMAKE_CXX_STANDARD 14)
add_executable(project_3 main.cpp includes/library.cpp includes/library.h includes/Polygon.h includes/linked_list.cpp includes/linked_list.h includes/graphics_handling.cpp includes/graphics_handling.h)

include_directories(SFML/include includes assets)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(project_3 ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
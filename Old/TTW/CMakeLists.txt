cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED True)

project(TTW)

add_executable(TTW TTW.cpp TTW_module.cpp)

add_subdirectory(flecs-master)

target_link_libraries(${PROJECT_NAME} flecs::flecs_static)

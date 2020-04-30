cmake_minimum_required(VERSION 3.16)
project(arkanoid_sfml)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

add_executable(arkanoid_sfml main.cpp)

target_link_libraries(arkanoid_sfml sfml-window sfml-graphics)
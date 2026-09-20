cmake_minimum_required(VERSION 3.10)
project(FallingSand)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib 4.5 REQUIRED)

add_executable(FallingSand main.cpp)

target_link_libraries(FallingSand raylib)
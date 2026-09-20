cmake_minimum_required(VERSION 4.1)
project(BlockBreak)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib 4.5 REQUIRED)

add_executable(BlockBreak main.cpp)

target_link_libraries(BlockBreak raylib)
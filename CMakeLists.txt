cmake_minimum_required(VERSION 2.6)

project(tada)

set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(example example.cpp)

cmake_minimum_required(VERSION 2.6)

project(tada)
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

# compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_CXX_FLAGS -Os)
endif()

# includes
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/mpfrc++")

# libraries
link_directories ("${PROJECT_SOURCE_DIR}/mpfrc++")

# project files
add_subdirectory(demos)
# add_subdirectory(tests)
enable_testing()

# external libraries
add_subdirectory(mpfrc++)

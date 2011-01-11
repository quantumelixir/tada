project(tada)

cmake_minimum_required(VERSION 2.6)

# set project name and version
set(APPLICATION_NAME ${PROJECT_NAME})
set(APPLICATION_VERSION "0.1")
set(APPLICATION_VERSION_MAJOR "0")
set(APPLICATION_VERSION_MINOR "1")

# cmake modules path
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
)

# macports
LINK_DIRECTORIES(/opt/local/lib/)

# disallow in-source build
include(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake /path/to/${PROJECT_NAME} [options]' there.")

# add definitions
include(DefineCMakeDefaults)
include(DefineCompilerFlags)
include(DefineInstallationPaths)

# c++ wrapper for mpfr
add_subdirectory(mpfrc++)

# common includes (for demos + tests)
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/mpfrc++")

# common libraries (for demos + tests)
link_directories ("${PROJECT_SOURCE_DIR}/mpfrc++")

# project files
add_subdirectory(demos)
add_subdirectory(tests)

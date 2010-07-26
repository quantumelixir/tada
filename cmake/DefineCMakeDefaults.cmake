# Always include srcdir and builddir in include path
# This saves typing ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY} in
# about every subdir
# since cmake 2.4.0
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Put the include dirs which are in the source or build tree
# before all other include dirs, so the headers in the sources
# are prefered over the already installed ones
# since cmake 2.4.1
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

# Use colored output
# since cmake 2.4.0
set(CMAKE_COLOR_MAKEFILE ON)

# Define the generic version of the libraries here
set(GENERIC_LIB_VERSION "0.1.0")
set(GENERIC_LIB_SOVERSION "0")

# Set the default build type to minimum size release (-Os)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE MinSizeRel
    CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE
  )
endif (NOT CMAKE_BUILD_TYPE)

# vim: set ts=4 sw=4 et:

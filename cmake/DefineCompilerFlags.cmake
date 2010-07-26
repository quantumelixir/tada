set(CMAKE_C_FLAGS     "-Wall -Wextra -Wformat=2")
set(CMAKE_C_FLAGS_DEBUG "-g3 -Werror -ggdb -O0 -DDEBUG")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_REWITHDEBINFO "-O2 -g")

add_definitions(-fwrapv)

# vim: set ts=4 sw=4 et:

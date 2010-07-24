add_definitions(-Wall -Wno-sign-compare -Wno-ctor-dtor-privacy -ggdb)
SET(COMMON test.cpp utilsTest.cpp)
add_executable(test ${COMMON})
target_link_libraries(test cppunit mpfrc++ mpfr gmp)

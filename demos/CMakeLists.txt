# utp demo
add_executable (utp_demo utp_demo.cpp)
target_link_libraries (utp_demo mpfrc++ mpfr gmp)

# mpfrc++ demo
add_executable (mpfrc++_demo mpfrc++_demo.cpp)
target_link_libraries (mpfrc++_demo mpfrc++ mpfr gmp)

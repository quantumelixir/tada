# dependencies
find_package(GMP)
find_package(MPFR)

if(GMP_FOUND AND MPFR_FOUND)
	message("Building optional mpfrc++ wrapper..")
	add_library (mpfrc++ mpreal.cpp)
else(GMP_FOUND AND MPFR_FOUND)
	message("Skip building optional mpfrc++ wrapper..")
endif(GMP_FOUND AND MPFR_FOUND)

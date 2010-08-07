# dependencies
find_package(GMP)
find_package(MPFR)

if(GMP_FOUND AND MPFR_FOUND)
	message("Making multiprecision demos..")

	include_directories(${GMP_INCLUDE_DIRS})
	include_directories(${MPFR_INCLUDE_DIRS})

	set(file_list "mp_mathfuncs.cpp")
	foreach(source ${file_list})
		get_filename_component(binary ${source} NAME_WE)
		add_executable (${binary} ${source})
		target_link_libraries(${binary} ${GMP_LIBRARIES})
		target_link_libraries(${binary} ${MPFR_LIBRARIES})
		target_link_libraries(${binary} mpfrc++)
	endforeach(source)

else(GMP_FOUND AND MPFR_FOUND)
	message("Not making multiprecision demos..")
endif(GMP_FOUND AND MPFR_FOUND)

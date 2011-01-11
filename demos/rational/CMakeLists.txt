# dependencies
find_package(GMP)

if(GMP_FOUND)
    message("Making demos using rational types..")

	include_directories(${GMP_INCLUDE_DIRS})

	set(file_list "rt_mathfuncs.cpp")
	foreach(source ${file_list})
		get_filename_component(binary ${source} NAME_WE)
		add_executable (${binary} ${source})
		target_link_libraries(${binary} gmpxx)
		target_link_libraries(${binary} gmp)
	endforeach(source)
else(GMP_FOUND)
    message("Not making demos using rational types..")
endif(GMP_FOUND)

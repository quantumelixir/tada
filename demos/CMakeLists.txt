include_directories(inc)
set(file_list "mathfuncs.cpp")
foreach(source ${file_list})
    get_filename_component(binary ${source} NAME_WE)
    add_executable (${binary} ${source})
endforeach(source)

add_subdirectory (multiprecision)

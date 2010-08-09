message("Making demos using complex types..")

set(file_list "cp_mathfuncs.cpp")
foreach(source ${file_list})
    get_filename_component(binary ${source} NAME_WE)
    add_executable (${binary} ${source})
endforeach(source)

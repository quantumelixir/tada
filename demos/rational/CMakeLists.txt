message("Making demos using rational types..")

set(file_list "rt_mathfuncs.cpp")
foreach(source ${file_list})
    get_filename_component(binary ${source} NAME_WE)
    add_executable (${binary} ${source})
endforeach(source)

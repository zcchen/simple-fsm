set(demo_dirs)
file(GLOB demo_c_files */*.cpp)
foreach(c ${demo_c_files})
    get_filename_component(dir ${c} DIRECTORY)
    if (NOT ${dir} IN_LIST demo_dirs)
        list(APPEND demo_dirs ${dir})
    endif()
endforeach()

foreach(demo ${demo_dirs})
    file(GLOB demo_srcs ${demo}/*.cpp)
    foreach(d_src ${demo_srcs})
        get_filename_component(d ${d_src} NAME_WLE)
        add_executable(${d} ${d_src})
        #target_link_libraries(${d} PUBLIC ${PROJECT_NAME}-lib)
        target_include_directories(${d} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    endforeach()
endforeach()


file(GLOB src_files ./*.cpp */*.cpp)

add_library(${PROJECT_NAME}-lib SHARED ${src_files})
set_target_properties(${PROJECT_NAME}-lib PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    SOVERSION ${PROJECT_VERSION}
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../include/
)
target_include_directories(${PROJECT_NAME}-lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(${PROJECT_NAME}-lib
)

install(TARGETS ${PROJECT_NAME}-lib)

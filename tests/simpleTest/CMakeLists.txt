file(GLOB simpleTest_src *.cpp)
add_executable(simpleTest ${simpleTest_src})
target_link_libraries(simpleTest
    PRIVATE ${test_libraries}
)
target_include_directories(simpleTest
    PRIVATE ${test_include_dirs}
)
add_test(NAME simpleTest COMMAND simpleTest)

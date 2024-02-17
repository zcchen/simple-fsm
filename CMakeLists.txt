cmake_minimum_required(VERSION 3.5)

PROJECT(simple-fsm
    VERSION 0.1.0
    LANGUAGES CXX
)

# ------------------ Compiler Settings ---------------------
#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# --------------- End of Compiler Settings -----------------

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
set(test_libraries Threads::Threads ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
set(test_include_dirs ${GTEST_INCLUDE_DIRS})
ENABLE_TESTING()

#ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(tests)

# Cmake file created with assistance from:
# https://www.youtube.com/watch?v=R3x2OvsUHOU - "How include SFML in CLion using CMAKE" - "Radoslaw Opacki"
# Project2 Catch Template - "Herschenglime"

cmake_minimum_required(VERSION 3.22)
project(map-nav)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

# pull in desired version of SFML, make it available
Include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.0
)
FetchContent_MakeAvailable(SFML)

# pull in desired version of catch through cmake automatically, make it available
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

include_directories(src)

add_executable(Main
        src/main.cpp  # main file
        src/gui.hpp
        src/gui.cpp
        src/nodemap.hpp
        src/nodemap.cpp
        src/traversals.hpp
        src/traversals.cpp
        # add other files above
        # example (can also separate with newlines):
        # src/BFS.h src/DFS.cpp
)

# These tests can use the Catch2-provided main
add_executable(Tests
        test/test.cpp  # test file
        src/gui.hpp
        src/gui.cpp
        src/nodemap.hpp
        src/nodemap.cpp
        src/traversals.hpp
        src/traversals.cpp
        # add other files above
        # example (can also separate with newlines):
        # src/BFS.h src/DFS.cpp
)

target_link_libraries(Main sfml-graphics)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain sfml-graphics) #link catch to test.cpp file

# comment everything below out if you are using CLion
# include(CTest)
# include(Catch)
# catch_discover_tests(Tests) # must be named the same as your test executable
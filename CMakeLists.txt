cmake_minimum_required(VERSION 3.0.0)
project(aktina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

enable_testing()
find_package(Catch2 3 REQUIRED)

# libraries
include_directories("${PROJECT_SOURCE_DIR}/aktina")

# geometry
add_library(libgeom STATIC aktina/vector.hpp)
set_target_properties(libgeom PROPERTIES LINKER_LANGUAGE CXX)

# float-compare
add_library(libfloat-compare STATIC aktina/float-compare.hpp)
set_target_properties(libfloat-compare PROPERTIES LINKER_LANGUAGE CXX)

# color
add_library(libcolor STATIC aktina/color.hpp)
set_target_properties(libcolor PROPERTIES LINKER_LANGUAGE CXX)

# canvas
add_library(libcanvas STATIC aktina/canvas.hpp)
set_target_properties(libcanvas PROPERTIES LINKER_LANGUAGE CXX)

# aktina tests
file(GLOB TEST_SOURCES "aktina/*.test.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain libgeom libfloat-compare libcolor)

include(CTest)
include(Catch)
catch_discover_tests(tests)

include(CPack)

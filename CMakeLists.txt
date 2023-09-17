cmake_minimum_required(VERSION 3.0.0)
project(aktina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

enable_testing()
find_package(Catch2 3 REQUIRED)

# prototypes
include_directories("${PROJECT_SOURCE_DIR}/prototype/geometry")
add_library(libgeom STATIC prototype/geometry/vector.hpp)
set_target_properties(libgeom PROPERTIES LINKER_LANGUAGE CXX)

# prototype tests
add_executable(tests prototype/geometry/vector.test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain libgeom)

include(CTest)
include(Catch)
catch_discover_tests(tests)

include(CPack)

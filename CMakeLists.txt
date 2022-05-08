# cmake version to be used
cmake_minimum_required( VERSION 3.15 )

# project name
project( matrix_cache LANGUAGES CXX )

# Location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
    )


set(BENCHMARK_ENABLE_TESTING OFF)

if((CMAKE_CXX_COMPILER_ID MATCHES GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
   set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11")
   set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
   set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()


include_directories( ./include )

add_subdirectory(./src )
add_subdirectory(./tests)
add_subdirectory(./benchmarks)

include(CTest)
include(GoogleTest)
include(GoogleBenchmark)


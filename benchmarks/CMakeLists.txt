set(BINARY ${CMAKE_PROJECT_NAME}_benchmarks)

file(GLOB_RECURSE BENCHMARK_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${BENCHMARK_SOURCES})

add_executable(${BINARY} ${BENCHMARK_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib benchmark)


# find_package(Threads REQUIRED)
#
# #~~~~~~~~~~~~~~~~
#
#
# file(GLOB_RECURSE ALL_BENCH_CPP *.cpp )
#
# foreach(ONE_BENCH_CPP ${ALL_BENCH_CPP})
#
#    get_filename_component(ONE_BENCH_EXEC ${ONE_BENCH_CPP} NAME_WE)
#
#    # Avoid name collision 
#    set(TARGET_NAME ${CMAKE_PROJECT_NAME}_benchmarks_${ONE_BENCH_EXEC})
#
#    add_executable(${TARGET_NAME} ${ONE_BENCH_CPP})
#    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_BENCH_EXEC}) 
#    target_link_libraries(${TARGET_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib
#
# # If required, you can add your project library here
# # ...
#          benchmark
#      ${CMAKE_THREAD_LIBS_INIT})
#
#    # If you want to run benchmarks with the "make test" command, uncomment me
#    add_test(${TARGET_NAME} ${ONE_BENCH_EXEC})
# endforeach()
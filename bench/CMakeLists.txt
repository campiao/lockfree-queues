FetchContent_Declare(benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.5
    GIT_SHALLOW TRUE
    SYSTEM)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)  # newer compilers add warnings to its sources
FetchContent_MakeAvailable(benchmark)

add_executable(lfq_bench_smoke
    smoke_bench.cpp)

target_link_libraries(lfq_bench_smoke PRIVATE
    lfq::lfq
    lfq_project_options
    benchmark::benchmark_main)

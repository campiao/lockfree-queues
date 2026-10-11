cmake_minimum_required(VERSION 3.25)

project(lockfree_queues
    VERSION 0.1.0
    DESCRIPTION "Lock-free SPSC/MPMC queues and a low-latency async logger"
    LANGUAGES CXX)

# Tests and benchmarks are on by default only when this is the top-level project,
# so consumers pulling us in via FetchContent just get the header-only library.
option(LFQ_BUILD_TESTS "Build unit and stress tests" ${PROJECT_IS_TOP_LEVEL})
option(LFQ_BUILD_BENCHMARKS "Build benchmarks" ${PROJECT_IS_TOP_LEVEL})
option(LFQ_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
option(LFQ_NATIVE_ARCH "Compile tests/benchmarks with -march=native" OFF)
set(LFQ_SANITIZER "" CACHE STRING "Sanitizer to enable: '', 'thread', or 'address,undefined'")

# ---------------------------------------------------------------------------
# Library (header-only)
# ---------------------------------------------------------------------------
add_library(lfq INTERFACE)
add_library(lfq::lfq ALIAS lfq)

target_include_directories(lfq INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(lfq INTERFACE cxx_std_23)

# ---------------------------------------------------------------------------
# Build settings for our own tests/benchmarks (never propagated to consumers)
# ---------------------------------------------------------------------------
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lfq_project_options INTERFACE)

target_compile_options(lfq_project_options INTERFACE
    -Wall -Wextra -Wpedantic
    -Wshadow -Wconversion -Wsign-conversion
    -Wold-style-cast -Wnon-virtual-dtor -Woverloaded-virtual
    $<$<BOOL:${LFQ_WARNINGS_AS_ERRORS}>:-Werror>
    $<$<BOOL:${LFQ_NATIVE_ARCH}>:-march=native>)

if(LFQ_SANITIZER)
    target_compile_options(lfq_project_options INTERFACE
        -fsanitize=${LFQ_SANITIZER} -fno-omit-frame-pointer -fno-sanitize-recover=all)
    target_link_options(lfq_project_options INTERFACE -fsanitize=${LFQ_SANITIZER})
endif()

# ---------------------------------------------------------------------------
# Subdirectories
# ---------------------------------------------------------------------------
include(FetchContent)

if(LFQ_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(LFQ_BUILD_BENCHMARKS)
    add_subdirectory(bench)
endif()

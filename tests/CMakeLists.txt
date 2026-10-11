FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
    SYSTEM)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(lfq_tests
    cache_line_test.cpp)

target_link_libraries(lfq_tests PRIVATE
    lfq::lfq
    lfq_project_options
    GTest::gtest_main)

gtest_discover_tests(lfq_tests)

cmake_minimum_required(VERSION 3.10)

project(
        STL
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(TARGET_TEST tests)

set(MORE_CXX_FLAGS "-std=c++17")
set(TESTFILE_FLAGS "")
set(TEST_FLAGS -Wall -Werror -Wextra -Wpedantic -g)
set(COVERAGE_FLAGS --coverage)

set(TEST_SOURCE tests/map_test.cc tests/array_test.cc tests/queue_test.cc tests/stack_test.cc)
set(MORE_CXX_FLAGS ${MORE_CXX_FLAGS} ${TEST_FLAGS} ${COVERAGE_FLAGS})
set(TESTFILE_FLAGS ${TESTFILE_FLAGS} ${TEST_FLAGS})
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)


find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${TARGET_TEST} ${TEST_SOURCE})
target_compile_features(${TARGET_TEST} PRIVATE cxx_std_17)
target_compile_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS} ${CMAKE_CXX_FLAGS})
target_link_options(${TARGET_TEST} PRIVATE ${TESTFILE_FLAGS} ${COVERAGE_FLAGS})

#file(GLOB SOURCES ./tests/*.cpp)
#add_executable(tests ${SOURCES})

target_link_libraries(${TARGET_TEST} GTest::gtest_main)

#gtest_discover_tests(tests)
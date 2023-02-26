cmake_minimum_required(VERSION 3.10)

project(
  STL
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
#set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

file(GLOB SOURCES /Users/dashakoroleva/CLionProjects/untitled2/tests/*.cpp)
add_executable(tests ${SOURCES})


target_link_libraries(tests GTest::gtest_main)

gtest_discover_tests(tests)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/$<CONFIG>")

file(GLOB_RECURSE SOURCES "core.cpp" "dependencies/*.c" "dependencies/*.cc" "dependencies/*.cpp")

project(benchmark LANGUAGES C CXX)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE tests dependencies)
cmake_minimum_required(VERSION 3.13)
project(bicudo)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")
include_directories(bicudo src)
add_executable(bicudo ${SOURCE_FILES})
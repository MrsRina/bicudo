# The main project setup var segment.
cmake_minimum_required(VERSION 3.13)
project(bicudo)

# The vars setup segment.
set(CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")

# Actions segment.
add_executable(bicudo ${SOURCE_FILES})

target_link_libraries(bicudo glew32 SDL2main SDL2 opengl32 mingw32)
include_directories(bicudo_test src)

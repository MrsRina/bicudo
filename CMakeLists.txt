# The main project setup var segment.
cmake_minimum_required(VERSION 3.13)
project(bicudo)
add_compile_options(-O0)

# Collect native source files and set compiler flags.
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH  ../build)
file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/api/client/*.cpp"
        "src/api/util/*.cpp"
        "src/api/render/*.cpp"
        "src/api/module/*.cpp"
        "src/api/scene/*.cpp"
        "src/api/service/*.cpp"
        "src/api/task/*.cpp"
        "src/api/feature/*.cpp"
        "src/api/gui/*.cpp"
        "src/api/physic/*.cpp"
        "src/api/physic/util/*.cpp"
        "src/api/physic/rigid/*.cpp"
        "src/api/world/util/*.cpp"
        "src/api/world/block/*.cpp"
        "src/api/world/entity/*.cpp"
        "src/api/world/chunk/*.cpp"
        "src/impl/scripts/*.cpp"
        "src/impl/scenes/*.cpp"
        "src/impl/context/*.cpp"
        )

# Add project src folder into include path.
include_directories(src)

# Add into executable and add libraries.
add_executable(bicudo ${SOURCE_FILES})
target_link_libraries(bicudo mingw32 glew32 SDL2main SDL2 SDL2_image opengl32)
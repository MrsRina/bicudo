cmake_minimum_required(VERSION 3.13)
project(bicudo)
add_compile_options(-O3)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH build/libs)
set(FINAL_NAME "")
set(LINK_LIBRARIES SDL2main)

if (WIN)
    set(FINAL_NAME "win-bicudo")
    set(LINK_LIBRARIES opengl32 freetype SDL2main SDL2 freetype)
else()
    set(FINAL_NAME "linux-bicudo")
    set(LINK_LIBRARIES GLEW GL SDL2main SDL2 freetype)
endif()

include_directories(source)
file(GLOB_RECURSE SOURCE_FILES "source/src/*.cpp")
add_library(bicudo ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${FINAL_NAME})

set(ENABLE_TESTS true)
if (${ENABLE_TESTS})
    file(GLOB_RECURSE SOURCE_FILES "tests/*.cpp")

    project(bicudo_tests)
    add_compile_options(-O3)

    set(CMAKE_CXX_STANDARD 17)
    set(EXECUTABLE_OUTPUT_PATH build/tests)

    include_directories(source)
    add_executable(bicudo_tests ${SOURCE_FILES})
    target_link_libraries(bicudo ${LINK_LIBRARIES})
endif()
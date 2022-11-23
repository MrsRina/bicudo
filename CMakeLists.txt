cmake_minimum_required(VERSION 3.13)
project(bicudo)
add_compile_options(-O3)

set(CMAKE_CXX_STANDARD 17)
set(LINK_LIBRARIES SDL2main)

if (WIN32)
    file(GLOB LIBRARY_PATH "./build/libs/win32/libbicudo.a")
    set(LIBRARY_OUTPUT_PATH ../build/libs/win32)
    set(LINK_LIBRARIES ${LIBRARY_PATH} mingw32 glew32 opengl32 SDL2main SDL2 freetype)
else()
    file(GLOB LIBRARY_PATH "./build/libs/linux/libbicudo.a")
    set(LIBRARY_OUTPUT_PATH ../build/libs/linux)
    set(LINK_LIBRARIES ${LIBRARY_PATH} GLEW GL SDL2main SDL2 freetype)
endif()

include_directories(source)
file(GLOB_RECURSE SOURCE_FILES "source/src/*.cpp")
add_library(bicudo ${SOURCE_FILES})

set(ENABLE_TESTS true)
if (${ENABLE_TESTS})
    file(GLOB_RECURSE SOURCE_FILES "tests/*.cpp")

    project(bicudo_tests)
    add_compile_options(-O3)

    set(CMAKE_CXX_STANDARD 17)
    set(EXECUTABLE_OUTPUT_PATH ../build/tests)

    include_directories(source)
    add_executable(bicudo_tests ${SOURCE_FILES})
    target_link_libraries(bicudo_tests ${LINK_LIBRARIES})
endif()
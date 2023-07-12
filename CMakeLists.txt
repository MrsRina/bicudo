cmake_minimum_required(VERSION 3.13)

project(bicudo)

add_compile_options(-O3)
include_directories(include)

set(CMAKE_CXX_STANDARD 17)
set(BICUDO_ENABLE_TESTS true)

if (WIN32)
    message("-- Setting Bicudo Win32")
    set(LIBRARY_OUTPUT_PATH ../build/libs/win32)
else()
    message("-- Setting Bicudo Linux")
    set(LIBRARY_OUTPUT_PATH ../build/libs/linux)
endif()

message("-- Bicudo configuring done")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_library(bicudo ${SOURCE_FILES})

message("-- Bicudo building done")

if (${BICUDO_ENABLE_TESTS})
    project(bicudo_tests)

    message("-- Bicudo tests enabled")

    if (WIN32)
        file(GLOB LIBRARY_PATH "./build/libs/win32/libbicudo.a")
        set(LINK_LIBRARIES ${LIBRARY_PATH} mingw32 glew32 opengl32 SDL2main SDL2 freetype)
    else()
        file(GLOB LIBRARY_PATH "./build/libs/linux/libbicudo.a")
        set(LINK_LIBRARIES ${LIBRARY_PATH} GLEW GL SDL2main SDL2 freetype)
    endif()

    message("-- Bicudo tests configuring done")

    set(EXECUTABLE_OUTPUT_PATH ../build/tests)
    file(GLOB_RECURSE SOURCE_FILES "tests/*.cpp")

    add_executable(bicudo_tests ${SOURCE_FILES})
    target_link_libraries(bicudo_tests ${LINK_LIBRARIES})

    message("-- Bicudo tests building done")
endif()
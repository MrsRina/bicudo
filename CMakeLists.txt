# The main project setup var segment.
cmake_minimum_required(VERSION 3.13)
project(bicudo)
add_compile_options(-O0)

# Collect native source files and set compiler flags.
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH  ../build)
set(EKG_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libekg.a")

file(GLOB_RECURSE SOURCE_FILES
        "src/main.cpp"
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

# Add project src folder into ekg path.
include_directories(src)

# Find EKG library.
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ekg/")
    message("-- Found EKG!")

    add_subdirectory(ekg/)
    include_directories(external/include)

    file(GLOB_RECURSE EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/*.hpp")

    foreach(file_i ${EKG_HEADER_FILES})
        file(REMOVE "${file_i}")
    endforeach(file_i)

    file(GLOB_RECURSE EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ekg/ekg/*.hpp")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg")

    message("-- Moving EKG header files!")

    foreach(file_i ${EKG_HEADER_FILES})
        file(COPY "${file_i}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/")
    endforeach(file_i)

    message("-- Copying EKG lib to libs!")

    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/ekg/lib/libekg.a" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/")
    message("-- EKG done!")
endif()

# Add into executable and add libraries.
add_executable(bicudo ${SOURCE_FILES})
target_link_libraries(bicudo "${EKG_LIB_DIR}" mingw32 glew32 opengl32 SDL2main SDL2 SDL2_image freetype-6)

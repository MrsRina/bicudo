# The main project setup var segment.
cmake_minimum_required(VERSION 3.13)
project(bicudo)
add_compile_options(-O3)

# Collect native source files and set compiler flags.
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH  ../build)
set(EKG_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libekg.a")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Add project src folder into ekg path.
include_directories(src)

# Find EKG library.
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ekg/")
    message("-- Found EKG!")
    message("-- Preparing to install EKG!")

    add_subdirectory(ekg/)
    include_directories(external/include)

    file(GLOB_RECURSE EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/*.hpp")

    foreach(file_i ${EKG_HEADER_FILES})
        file(REMOVE "${file_i}")
    endforeach(file_i)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg" "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/api" "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/impl")

    message("-- Installing EKG core!")
    file(GLOB EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ekg/include/ekg/*.hpp")

    foreach(file_i ${EKG_HEADER_FILES})
        file(COPY "${file_i}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg")
    endforeach(file_i)

    message("-- Installing EKG API!")
    file(GLOB EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ekg/include/ekg/api/*.hpp")

    foreach(file_i ${EKG_HEADER_FILES})
        file(COPY "${file_i}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/api")
    endforeach(file_i)

    message("-- Installing EKG implements!")
    file(GLOB EKG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ekg/include/ekg/impl/*.hpp")

    foreach(file_i ${EKG_HEADER_FILES})
        file(COPY "${file_i}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/include/ekg/impl")
    endforeach(file_i)

    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/ekg/lib/libekg.a" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/")
    message("-- EKG done!")
endif()

# Add into executable and add libraries.
add_executable(bicudo ${SOURCE_FILES})
target_link_libraries(bicudo "${EKG_LIB_DIR}" mingw32 glew32 opengl32 SDL2main SDL2 freetype)
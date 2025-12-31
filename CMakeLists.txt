cmake_minimum_required(VERSION 3.20)

project(media-xray VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(MEDIAXRAY_GIT_HASH "unknown")
find_package(Git QUIET)
if (GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE MEDIAXRAY_GIT_RESULT
        OUTPUT_VARIABLE MEDIAXRAY_GIT_OUTPUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    if (MEDIAXRAY_GIT_RESULT EQUAL 0 AND NOT MEDIAXRAY_GIT_OUTPUT STREQUAL "")
        set(MEDIAXRAY_GIT_HASH "${MEDIAXRAY_GIT_OUTPUT}")
    endif()
endif()

add_subdirectory(core)
add_subdirectory(cli)
add_subdirectory(src)
add_subdirectory(tests)

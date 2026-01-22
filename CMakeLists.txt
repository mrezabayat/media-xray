cmake_minimum_required(VERSION 3.25)

project(mediaxray C)

# --------------------
# Global settings
# --------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build unit tests" ON)

# --------------------
# Subdirectories
# --------------------
add_subdirectory(core)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

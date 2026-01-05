add_library(media_xray_core
    log.cpp
    version.cpp
)

find_package(spdlog CONFIG REQUIRED)

target_include_directories(media_xray_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(media_xray_core PUBLIC
    MEDIAXRAY_VERSION="${PROJECT_VERSION}"
    MEDIAXRAY_GIT_HASH="${MEDIAXRAY_GIT_HASH}"
)

target_link_libraries(media_xray_core PUBLIC spdlog::spdlog)

if (MSVC)
    target_compile_options(media_xray_core PRIVATE /W4)
else()
    target_compile_options(media_xray_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_library(media_xray_core
    version.cpp
)

target_include_directories(media_xray_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(media_xray_core PUBLIC
    MEDIAXRAY_VERSION="${PROJECT_VERSION}"
    MEDIAXRAY_GIT_HASH="${MEDIAXRAY_GIT_HASH}"
)

if (MSVC)
    target_compile_options(media_xray_core PRIVATE /W4)
else()
    target_compile_options(media_xray_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

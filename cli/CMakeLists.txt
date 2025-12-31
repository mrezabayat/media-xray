find_package(cxxopts CONFIG REQUIRED)

add_library(media_xray_cli
    cli.cpp
)

target_link_libraries(media_xray_cli PUBLIC media_xray_core)
target_link_libraries(media_xray_cli PUBLIC cxxopts::cxxopts)

target_include_directories(media_xray_cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if (MSVC)
    target_compile_options(media_xray_cli PRIVATE /W4)
else()
    target_compile_options(media_xray_cli PRIVATE -Wall -Wextra -Wpedantic)
endif()

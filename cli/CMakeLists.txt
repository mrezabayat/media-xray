find_package(cxxopts CONFIG REQUIRED)

add_executable(media-xray
    main.cpp
)

target_link_libraries(media-xray PRIVATE media_xray_core)
target_link_libraries(media-xray PRIVATE cxxopts::cxxopts)

if (MSVC)
    target_compile_options(media-xray PRIVATE /W4)
else()
    target_compile_options(media-xray PRIVATE -Wall -Wextra -Wpedantic)
endif()

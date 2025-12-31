add_executable(media-xray
    main.cpp
)

target_link_libraries(media-xray PRIVATE media_xray_cli)

if (MSVC)
    target_compile_options(media-xray PRIVATE /W4)
else()
    target_compile_options(media-xray PRIVATE -Wall -Wextra -Wpedantic)
endif()

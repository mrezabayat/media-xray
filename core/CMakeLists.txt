add_library(mediaxray_core STATIC
    hls/hls_invariants.c
)

target_include_directories(mediaxray_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_compile_options(mediaxray_core PRIVATE
    -Wall
    -Wextra
    -Werror
)

add_library(mediaxray_analysis STATIC
    segment_timing_validator.c
    variant_alignment_analyzer.c
    playlist_consistency_checker.c
)

target_link_libraries(mediaxray_analysis
    mediaxray_core
)

target_compile_options(mediaxray_analysis PRIVATE
    -Wall -Wextra -Werror
)

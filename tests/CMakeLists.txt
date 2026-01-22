add_executable(test_hls_invariants
    core/test_hls_invariants.c
)

target_include_directories(test_hls_invariants
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(test_hls_invariants
    mediaxray_core
)

add_test(
    NAME core_hls_invariants
    COMMAND test_hls_invariants
)

enable_testing()

function(add_c_test TEST_SOURCE LINK_LIBS)
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SOURCE})

    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
            ${LINK_LIBS}
    )

    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )
endfunction()


file(GLOB_RECURSE CORE_TESTS
    core/test_*.c
)

file(GLOB_RECURSE ANALYSIS_TESTS
    analysis/test_*.c
)

foreach(test_file ${CORE_TESTS})
    add_c_test(${test_file} mediaxray_core)
endforeach()

foreach(test_file ${ANALYSIS_TESTS})
    add_c_test(${test_file} mediaxray_analysis)
endforeach()

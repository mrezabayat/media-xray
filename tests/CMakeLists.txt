find_package(GTest CONFIG REQUIRED)

add_executable(test_basic
    test_basic.cpp
)

target_link_libraries(test_basic PRIVATE media_xray_core)
target_link_libraries(test_basic PRIVATE GTest::gtest_main)

add_test(NAME test_basic COMMAND test_basic)

if (MSVC)
    target_compile_options(test_basic PRIVATE /W4)
else()
    target_compile_options(test_basic PRIVATE -Wall -Wextra -Wpedantic)
endif()

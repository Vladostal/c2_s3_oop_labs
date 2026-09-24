add_library(lab1_core STATIC src/array_ops.cpp)
target_include_directories(lab1_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
lab_warnings(lab1_core)

add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE lab1_core)
lab_warnings(lab1)

add_executable(lab1_tests tests/test_variant.cpp)
target_link_libraries(lab1_tests PRIVATE lab1_core GTest::gtest_main)
lab_warnings(lab1_tests)
gtest_discover_tests(lab1_tests)

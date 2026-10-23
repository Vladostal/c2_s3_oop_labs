add_library(lab2_core STATIC src/matrix.cpp)
target_include_directories(lab2_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
lab_warnings(lab2_core)

add_executable(lab2 src/main.cpp)
target_link_libraries(lab2 PRIVATE lab2_core)
lab_warnings(lab2)

add_executable(lab2_tests tests/tests.cpp)
target_link_libraries(lab2_tests PRIVATE lab2_core GTest::gtest_main)
lab_warnings(lab2_tests)
gtest_discover_tests(lab2_tests)

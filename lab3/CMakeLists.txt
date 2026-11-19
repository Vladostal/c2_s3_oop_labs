add_library(lab3_core STATIC src/temperature.cpp src/temperature_set.cpp)
target_include_directories(lab3_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
lab_warnings(lab3_core)

add_executable(lab3 src/main.cpp)
target_link_libraries(lab3 PRIVATE lab3_core)
lab_warnings(lab3)

add_executable(lab3_tests tests/tests.cpp)
target_link_libraries(lab3_tests PRIVATE lab3_core GTest::gtest_main)
lab_warnings(lab3_tests)
gtest_discover_tests(lab3_tests)

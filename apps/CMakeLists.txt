add_executable(weighted_popcnt main.cpp)
target_link_libraries(weighted_popcnt PRIVATE weighted_popcnt_lib benchmark::benchmark)

add_executable(unittest
    unittest_SparseChain.cpp
    unittest_VectorChain.cpp
    unittest_BitChain.cpp
)
target_link_libraries(unittest PRIVATE weighted_popcnt_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittest)

add_executable(test_core test_core.cpp)
target_link_libraries(test_core PRIVATE hasklib)
add_test(NAME core COMMAND test_core)

add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE hasklib)
add_test(NAME stats COMMAND test_stats)
add_executable(test_core test_core.cpp)
target_link_libraries(test_core PRIVATE hasklib)
add_test(NAME core COMMAND test_core)

add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE hasklib)
add_test(NAME stats COMMAND test_stats)

add_executable(test_stochastic test_stochastic.cpp)
target_link_libraries(test_stochastic PRIVATE hasklib)
add_test(NAME test_stochastic COMMAND test_stochastic)


add_executable(out1 move_Test.cc)

target_link_libraries(out1 gtest gtest_main pthread board)

add_test(test_move ./out1)


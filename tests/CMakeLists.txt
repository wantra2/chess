

add_executable(out1 move_Test.cc)
add_executable(out2 adapter_Test.cc)
add_executable(out3 movegen_knight_Test.cc)
add_executable(out4 movegen_king_Test.cc)


target_link_libraries(out1 gtest gtest_main pthread move)
target_link_libraries(out2 gtest gtest_main pthread board move)
target_link_libraries(out3 gtest gtest_main pthread board move)
target_link_libraries(out4 gtest gtest_main pthread board move)


add_test(test_move ./out1)
add_test(test_adapter ./out2)
add_test(test_movegen_knight ./out3)
add_test(test_movegen_king ./out4)

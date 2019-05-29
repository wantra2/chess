

add_executable(out1 move_Test.cc)
add_executable(out2 adapter_Test.cc)
add_executable(out3 movegen_knight_Test.cc)
add_executable(out4 movegen_king_Test.cc)
add_executable(out5 movegen_pawn_Test.cc)
add_executable(out6 movegen_slidin_Test.cc)
add_executable(out7 movegen_castlings_Test.cc)


target_link_libraries(out1 gtest gtest_main pthread board move)
target_link_libraries(out2 gtest gtest_main pthread board move)
target_link_libraries(out3 gtest gtest_main pthread board move)
target_link_libraries(out4 gtest gtest_main pthread board move)
target_link_libraries(out5 gtest gtest_main pthread board move)
target_link_libraries(out6 gtest gtest_main pthread board move)
target_link_libraries(out7 gtest gtest_main pthread board move)

add_test(test_move ./out1)
add_test(test_adapter ./out2)
add_test(test_movegen_knight ./out3)
add_test(test_movegen_king ./out4)
add_test(test_movegen_pawn ./out5)
add_test(test_movegen_sliding ./out6)
add_test(test_movegen_castlings ./out7)

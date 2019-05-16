

add_executable(test_movegen movegen_Test.cc)

target_link_libraries(test_movegen gtest gtest_main pthread)

add_test(moveGen ./test_movegen)


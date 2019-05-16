#include <gtest/gtest.h>
#include <iostream>

TEST(testsuite, test1)
{
  ASSERT_EQ(4, 4);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

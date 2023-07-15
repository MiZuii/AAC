#include<gtest/gtest.h>

// Test headers are compiled in cmake

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
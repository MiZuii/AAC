#include <gtest/gtest.h>

#ifdef TEST_HEADERS
#include TEST_HEADERS
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
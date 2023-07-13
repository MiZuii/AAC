#include <gtest/gtest.h>
#include <AAC.h>

using namespace ::testing;
using namespace AAC;

// class MatrixConstructorTest : public ::testing::Test {
// public:
//     Matrix<int> m;

// protected:

//     void SetUp() override {
//         m = Matrix<int>(10, 10);
//         m[0][0] = 5;
//     }
// };


TEST(MatrixTest, NoArgumentConstructor) {

    Matrix<char> m;
    ASSERT_EQ(m.GetXSize(), 0);
    ASSERT_EQ(m.GetYSize(), 0);

}


// TEST_F(MatrixConstructorTest, Constructor) {
//     ASSERT_EQ(m.GetXSize(), 10);
//     ASSERT_EQ(m.GetYSize(), 10);
// }

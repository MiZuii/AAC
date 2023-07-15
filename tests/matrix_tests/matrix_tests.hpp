#include <gtest/gtest.h>
#include <aac.h>

using namespace ::testing;
using namespace AAC;

// class MatrixConstructorTest : public ::testing::Test {
// public:
//     Matrix<int> m;

// protected:

//     void SetUp() override {
//         m = Matrix<int>(10, 10);
//     }
// };


TEST(MatrixTest, NoArgumentConstructor) {

    Matrix<char> m;

    ASSERT_EQ(m.GetXSize(), 0);
    ASSERT_EQ(m.GetYSize(), 0);

}

TEST(MatrixTest, ArgumentConstructor) {

    Matrix<char> m(5, 9);

    ASSERT_EQ(m.GetXSize(), 5);
    ASSERT_EQ(m.GetYSize(), 9);

}

TEST(MatrixTest, CopyConstructor) {

    Matrix<int> m(6, 5);
    auto m2 = m;

    ASSERT_EQ(m2.GetXSize(), 6);
    ASSERT_EQ(m2.GetYSize(), 5);

}

TEST(MatrixTest, AssignmentOperator) {

    auto m2 = Matrix<int>(6, 5);

    ASSERT_EQ(m2.GetXSize(), 6);
    ASSERT_EQ(m2.GetYSize(), 5);

}

TEST(MatrixTest, ZeroQuantityPrevention) {

    Matrix<int> m;

    ASSERT_THROW(m[0][0], AACException);

}

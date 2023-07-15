#include <gtest/gtest.h>
#include <aac.h>

using namespace ::testing;
using namespace AAC;

#define MAKE_STR(x) _MAKE_STR(x)
#define _MAKE_STR(x) #x

#ifndef TEST_RESOURCE_1
    #define MISSING_RESOURCES
    #define TEST_RESOURCE_1 // for compilation errors
#endif

#ifndef TEST_RESOURCE_2
    #define MISSING_RESOURCES
    #define TEST_RESOURCE_2 // for compilation errors
#endif

class ImageTests : public ::testing::Test
{
protected:
    void SetUp() override {
#ifdef MISSING_RESOURCES
        ADD_FAILURE() << "Tests resources not found";
#endif
    }
};


TEST_F(ImageTests, CreateImageFromPath) {

    ASSERT_NO_THROW(Image png(MAKE_STR(TEST_RESOURCE_1)));
    ASSERT_NO_THROW(Image png(MAKE_STR(TEST_RESOURCE_2)));
    ASSERT_THROW(Image err("notexistingimage"), AACException);

}

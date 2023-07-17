#include <gtest/gtest.h>
#include <aac.h>
#include <ttf_reader.h>

using namespace ::testing;
using namespace AAC;

#define MAKE_STR(x) _MAKE_STR(x)
#define _MAKE_STR(x) #x

#ifndef TEST_RESOURCE_3
    #define MISSING_RESOURCES
    #define TEST_RESOURCE_3 // for compilation errors
#endif

class TTFReaderTests : public ::testing::Test
{
protected:
    void SetUp() override {
#ifdef MISSING_RESOURCES
        ADD_FAILURE() << "Tests resources not found";
#endif
    }
};


TEST_F(TTFReaderTests, SimpleTest) {

    
    int ret;
    ttf_data dat;

    ret = create_ttf_data(&dat, MAKE_STR(TEST_RESOURCE_3));

    ASSERT_EQ(ret, 0);

}

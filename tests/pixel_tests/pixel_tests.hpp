#include <gtest/gtest.h>
#include <aac.h>

using namespace ::testing;
using namespace AAC;

TEST(PixelTests, NoArgumentConstructor) {
    
    Pixel<Pixel_Type::G> pg;
    Pixel<Pixel_Type::GA> pga;
    Pixel<Pixel_Type::RGB> prgb;
    Pixel<Pixel_Type::RGBA> prgba;

    ASSERT_EQ(pg.GetPixelValues().grey, 0);

    ASSERT_EQ(pga.GetPixelValues().grey, 0);
    ASSERT_EQ(pga.GetPixelValues().alpha, 0);

    ASSERT_EQ(prgb.GetPixelValues().red, 0);
    ASSERT_EQ(prgb.GetPixelValues().green, 0);
    ASSERT_EQ(prgb.GetPixelValues().blue, 0);

    ASSERT_EQ(prgba.GetPixelValues().red, 0);
    ASSERT_EQ(prgba.GetPixelValues().green, 0);
    ASSERT_EQ(prgba.GetPixelValues().blue, 0);
    ASSERT_EQ(prgba.GetPixelValues().alpha, 0);

}

TEST(PixelTests, ArgumentConstructor) {
    
    Pixel<Pixel_Type::G> pg(1);
    Pixel<Pixel_Type::GA> pga(1, 2);
    Pixel<Pixel_Type::RGB> prgb(1, 2, 3);
    Pixel<Pixel_Type::RGBA> prgba(1, 2, 3, 4);

    ASSERT_EQ(pg.GetPixelValues().grey, 1);

    ASSERT_EQ(pga.GetPixelValues().grey, 1);
    ASSERT_EQ(pga.GetPixelValues().alpha, 2);

    ASSERT_EQ(prgb.GetPixelValues().red, 1);
    ASSERT_EQ(prgb.GetPixelValues().green, 2);
    ASSERT_EQ(prgb.GetPixelValues().blue, 3);

    ASSERT_EQ(prgba.GetPixelValues().red, 1);
    ASSERT_EQ(prgba.GetPixelValues().green, 2);
    ASSERT_EQ(prgba.GetPixelValues().blue, 3);
    ASSERT_EQ(prgba.GetPixelValues().alpha, 4);

}

TEST(PixelTests, SetValues) {
    
    Pixel<Pixel_Type::G> pg(1);
    Pixel<Pixel_Type::GA> pga(1, 2);
    Pixel<Pixel_Type::RGB> prgb(1, 2, 3);
    Pixel<Pixel_Type::RGBA> prgba(1, 2, 3, 4);

    pg.SetPixelValues(5);
    pga.SetPixelValues(5, 6);
    prgb.SetPixelValues(5, 6, 7);
    prgba.SetPixelValues(5, 6, 7, 8);

    ASSERT_EQ(pg.GetPixelValues().grey, 5);

    ASSERT_EQ(pga.GetPixelValues().grey, 5);
    ASSERT_EQ(pga.GetPixelValues().alpha, 6);

    ASSERT_EQ(prgb.GetPixelValues().red, 5);
    ASSERT_EQ(prgb.GetPixelValues().green, 6);
    ASSERT_EQ(prgb.GetPixelValues().blue, 7);

    ASSERT_EQ(prgba.GetPixelValues().red, 5);
    ASSERT_EQ(prgba.GetPixelValues().green, 6);
    ASSERT_EQ(prgba.GetPixelValues().blue, 7);
    ASSERT_EQ(prgba.GetPixelValues().alpha, 8);

}

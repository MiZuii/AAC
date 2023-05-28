#include "../AAC.h"

/* -------------------------------- GREY TYPE ------------------------------- */

AAC_Pixel<AAC_Pixel_Type::G>::AAC_Pixel(uint8_t grey)
{
    _pixel_values.grey = grey;
}

AAC_Pixel<AAC_Pixel_Type::G>::AAC_Pixel() : AAC_Pixel(0) {}

struct AAC_Pixel_G AAC_Pixel<AAC_Pixel_Type::G>::GetPixelValues()
{
    return _pixel_values;
}

void
AAC_Pixel<AAC_Pixel_Type::G>::SetPixelValues(uint8_t grey)
{
    _pixel_values.grey = grey;
}

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */

AAC_Pixel<AAC_Pixel_Type::GA>::AAC_Pixel(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

AAC_Pixel<AAC_Pixel_Type::GA>::AAC_Pixel() : AAC_Pixel(0, 0) {}

struct AAC_Pixel_GA AAC_Pixel<AAC_Pixel_Type::GA>::GetPixelValues()
{
    return _pixel_values;
}

void
AAC_Pixel<AAC_Pixel_Type::GA>::SetPixelValues(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */

AAC_Pixel<AAC_Pixel_Type::RGB>::AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

AAC_Pixel<AAC_Pixel_Type::RGB>::AAC_Pixel() : AAC_Pixel(0, 0, 0) {}

struct AAC_Pixel_RGB AAC_Pixel<AAC_Pixel_Type::RGB>::GetPixelValues()
{
    return _pixel_values;
}

void
AAC_Pixel<AAC_Pixel_Type::RGB>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */

AAC_Pixel<AAC_Pixel_Type::RGBA>::AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

AAC_Pixel<AAC_Pixel_Type::RGBA>::AAC_Pixel() : AAC_Pixel(0, 0, 0, 0) {}

struct AAC_Pixel_RGBA AAC_Pixel<AAC_Pixel_Type::RGBA>::GetPixelValues()
{
    return _pixel_values;
}

void AAC_Pixel<AAC_Pixel_Type::RGBA>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

/* ---------------------------------- EMPTY --------------------------------- */

AAC_Pixel<AAC_Pixel_Type::EMPTY>::AAC_Pixel()
{
    // empty for now
}
#include "../AAC.h"

/* -------------------------------- GREY TYPE ------------------------------- */

AAC::Pixel<AAC::Pixel_Type::G>::Pixel(uint8_t grey)
{
    _pixel_values.grey = grey;
}

AAC::Pixel<AAC::Pixel_Type::G>::Pixel() : AAC::Pixel<AAC::Pixel_Type::G>(0) {}

struct AAC::Pixel_G AAC::Pixel<AAC::Pixel_Type::G>::GetPixelValues()
{
    return _pixel_values;
}

void AAC::Pixel<AAC::Pixel_Type::G>::SetPixelValues(uint8_t grey)
{
    _pixel_values.grey = grey;
}

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */

AAC::Pixel<AAC::Pixel_Type::GA>::Pixel(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

AAC::Pixel<AAC::Pixel_Type::GA>::Pixel() : AAC::Pixel<AAC::Pixel_Type::GA>(0, 0) {}

struct AAC::Pixel_GA AAC::Pixel<AAC::Pixel_Type::GA>::GetPixelValues()
{
    return _pixel_values;
}

void AAC::Pixel<AAC::Pixel_Type::GA>::SetPixelValues(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */

AAC::Pixel<AAC::Pixel_Type::RGB>::Pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

AAC::Pixel<AAC::Pixel_Type::RGB>::Pixel() : AAC::Pixel<AAC::Pixel_Type::RGB>(0, 0, 0) {}

struct AAC::Pixel_RGB AAC::Pixel<AAC::Pixel_Type::RGB>::GetPixelValues()
{
    return _pixel_values;
}

void AAC::Pixel<AAC::Pixel_Type::RGB>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */

AAC::Pixel<AAC::Pixel_Type::RGBA>::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

AAC::Pixel<AAC::Pixel_Type::RGBA>::Pixel() : AAC::Pixel<AAC::Pixel_Type::RGBA>(0, 0, 0, 0) {}

struct AAC::Pixel_RGBA AAC::Pixel<AAC::Pixel_Type::RGBA>::GetPixelValues()
{
    return _pixel_values;
}

void AAC::Pixel<AAC::Pixel_Type::RGBA>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

/* ---------------------------------- EMPTY --------------------------------- */

AAC::Pixel<AAC::Pixel_Type::EMPTY>::Pixel()
{
    // empty for now
}
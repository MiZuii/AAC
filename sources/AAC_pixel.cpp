#include "../AAC.h"

/* -------------------------------- GREY TYPE ------------------------------- */

/**
 * @brief Constructs a Pixel object with the specified grey value.
 * @param grey The grey value.
 */
AAC::Pixel<AAC::Pixel_Type::G>::Pixel(uint8_t grey)
{
    _pixel_values.grey = grey;
}

/**
 * @brief Default constructor for a Pixel object with a grey value of 0.
 */
AAC::Pixel<AAC::Pixel_Type::G>::Pixel() : AAC::Pixel<AAC::Pixel_Type::G>(0) {}

/**
 * @brief Retrieves the pixel values.
 * @return The pixel values.
 */
struct AAC::Pixel_G AAC::Pixel<AAC::Pixel_Type::G>::GetPixelValues()
{
    return _pixel_values;
}

/**
 * @brief Sets the pixel values to the specified grey value.
 * @param grey The grey value.
 */
void AAC::Pixel<AAC::Pixel_Type::G>::SetPixelValues(uint8_t grey)
{
    _pixel_values.grey = grey;
}

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */

/**
 * @brief Constructs a Pixel object with the specified grey and alpha values.
 * @param grey The grey value.
 * @param alpha The alpha value.
 */
AAC::Pixel<AAC::Pixel_Type::GA>::Pixel(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

/**
 * @brief Default constructor for a Pixel object with grey and alpha values of 0.
 */
AAC::Pixel<AAC::Pixel_Type::GA>::Pixel() : AAC::Pixel<AAC::Pixel_Type::GA>(0, 0) {}

/**
 * @brief Retrieves the pixel values.
 * @return The pixel values.
 */
struct AAC::Pixel_GA AAC::Pixel<AAC::Pixel_Type::GA>::GetPixelValues()
{
    return _pixel_values;
}

/**
 * @brief Sets the pixel values to the specified grey and alpha values.
 * @param grey The grey value.
 * @param alpha The alpha value.
 */
void AAC::Pixel<AAC::Pixel_Type::GA>::SetPixelValues(uint8_t grey, uint8_t alpha)
{
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */

/**
 * @brief Constructs a Pixel object with the specified red, green, and blue values.
 * @param red The red value.
 * @param green The green value.
 * @param blue The blue value.
 */
AAC::Pixel<AAC::Pixel_Type::RGB>::Pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

/**
 * @brief Default constructor for a Pixel object with red, green, and blue values of 0.
 */
AAC::Pixel<AAC::Pixel_Type::RGB>::Pixel() : AAC::Pixel<AAC::Pixel_Type::RGB>(0, 0, 0) {}

/**
 * @brief Retrieves the pixel values.
 * @return The pixel values.
 */
struct AAC::Pixel_RGB AAC::Pixel<AAC::Pixel_Type::RGB>::GetPixelValues()
{
    return _pixel_values;
}

/**
 * @brief Sets the pixel values to the specified red, green, and blue values.
 * @param red The red value.
 * @param green The green value.
 * @param blue The blue value.
 */
void AAC::Pixel<AAC::Pixel_Type::RGB>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */

/**
 * @brief Constructs a Pixel object with the specified red, green, blue, and alpha values.
 * @param red The red value.
 * @param green The green value.
 * @param blue The blue value.
 * @param alpha The alpha value.
 */
AAC::Pixel<AAC::Pixel_Type::RGBA>::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

/**
 * @brief Default constructor for a Pixel object with red, green, blue, and alpha values of 0.
 */
AAC::Pixel<AAC::Pixel_Type::RGBA>::Pixel() : AAC::Pixel<AAC::Pixel_Type::RGBA>(0, 0, 0, 0) {}

/**
 * @brief Retrieves the pixel values.
 * @return The pixel values.
 */
struct AAC::Pixel_RGBA AAC::Pixel<AAC::Pixel_Type::RGBA>::GetPixelValues()
{
    return _pixel_values;
}

/**
 * @brief Sets the pixel values to the specified red, green, blue, and alpha values.
 * @param red The red value.
 * @param green The green value.
 * @param blue The blue value.
 * @param alpha The alpha value.
 */
void AAC::Pixel<AAC::Pixel_Type::RGBA>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}

/* ---------------------------------- EMPTY --------------------------------- */

/**
 * @brief Default constructor for an empty Pixel object.
 */
AAC::Pixel<AAC::Pixel_Type::EMPTY>::Pixel()
{
    // empty for now
}

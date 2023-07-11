#include "../AAC.h"

/**
 * @file AAC_BC_Simple.cpp
 * @brief Contains the implementation of the AAC::BC_Simple class.
 */

/* -------------------------------------------------------------------------- */
/*                                AAC_BC_Simple                               */
/* -------------------------------------------------------------------------- */

/**
 * @brief Constructs a new AAC::BC_Simple object with the specified weights and negate flag.
 *
 * @param red_weight The weight for the red channel.
 * @param green_weight The weight for the green channel.
 * @param blue_weight The weight for the blue channel.
 * @param negate Flag indicating whether to negate the brightness values.
 */
AAC::BC_Simple::BC_Simple(float red_weight, float green_weight, float blue_weight, uint8_t negate) :
    _red_weight(red_weight), _green_weight(green_weight), _blue_weight(blue_weight), _negate(negate) {}

/**
 * @brief Constructs a new AAC::BC_Simple object with default weights and negate flag.
 *        The default weights are 1 for all channels.
 */
AAC::BC_Simple::BC_Simple() : AAC::BC_Simple::BC_Simple(1, 1, 1) {}

/**
 * @brief Converts the given image to a brightness matrix using the specified weights and negate flag.
 *
 * @param img A pointer to the image to be converted.
 * @return A shared pointer to the resulting brightness matrix.
 *
 * @throws AAC::error_code An exception is thrown if the pixel type is invalid.
 */
std::shared_ptr<AAC::Matrix<uint8_t>> AAC::BC_Simple::convert(AAC::Image* img) {
    std::shared_ptr<AAC::Matrix<uint8_t>> brightness_matrix(new AAC::Matrix<uint8_t>(img->size_x, img->size_y));
    void *raw_pixels_matrix = img->GetMatrix();

    for (msize_t y = 0; y < img->size_y; y++)
    {
        for (msize_t x = 0; x < img->size_x; x++)
        {
            switch (img->pixel_type)
            {
            case AAC::Pixel_Type::G:
            {
                AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>> *pixels_g = reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>> *>(raw_pixels_matrix);

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * ((*pixels_g)[y][x].GetPixelValues().grey*(_red_weight + _green_weight + _blue_weight)/3);
                break;
            }
            case AAC::Pixel_Type::GA:
            {
                AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>> *pixels_ga = reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>> *>(raw_pixels_matrix);
                struct AAC::Pixel_GA ga = (*pixels_ga)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * ((ga.grey + ga.alpha)*(_red_weight + _green_weight + _blue_weight)/3 / 2);
                break;
            }
            case AAC::Pixel_Type::RGB:
            {
                AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>> *pixels_rgb = reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>> *>(raw_pixels_matrix);
                struct AAC::Pixel_RGB rgb = (*pixels_rgb)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * (rgb.red*_red_weight / 3 + rgb.green*_green_weight / 3 + rgb.blue*_blue_weight / 3);
                break;
            }
            case AAC::Pixel_Type::RGBA:
            {
                AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>> *pixels_rgba = reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>> *>(raw_pixels_matrix);
                struct AAC::Pixel_RGBA rgba = (*pixels_rgba)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * (rgba.red*(_red_weight / 6) + rgba.green*(_green_weight / 6) + rgba.blue*(_blue_weight / 6) + rgba.alpha / 2);
                break;
            }
            default:
                AAC::set_error_code(AAC::make_error_code(AAC::error_codes::INVALID_PIXEL));
                throw AAC::get_error_code();
                break;
            }
        }
    }

    return brightness_matrix;
}

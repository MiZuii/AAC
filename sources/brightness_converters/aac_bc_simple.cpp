#include <aac.h>

/**
 * @file aac_bc_simple.cpp
 * @brief Contains the implementation of the AAC::BC_Simple class.
 */

using namespace AAC;

/**
 * @brief Constructs a new BC_Simple object with the specified weights and negate flag.
 *
 * @param red_weight The weight for the red channel.
 * @param green_weight The weight for the green channel.
 * @param blue_weight The weight for the blue channel.
 * @param negate Flag indicating whether to negate the brightness values.
 */
BC_Simple::BC_Simple(float red_weight, float green_weight, float blue_weight, uint8_t negate) :
    _red_weight(red_weight), _green_weight(green_weight), _blue_weight(blue_weight), _negate(negate) {}

/**
 * @brief Constructs a new BC_Simple object with default weights and negate flag.
 *        The default weights are 1 for all channels.
 */
BC_Simple::BC_Simple() : BC_Simple::BC_Simple(1, 1, 1) {}

/**
 * @brief Converts the given image to a brightness matrix using the specified weights and negate flag.
 *
 * @param img A pointer to the image to be converted.
 * @return A shared pointer to the resulting brightness matrix.
 *
 * @throws error_code An exception is thrown if the pixel type is invalid.
 */
std::shared_ptr<Matrix<uint8_t>> BC_Simple::convert(Image* img) {
    std::shared_ptr<Matrix<uint8_t>> brightness_matrix(new Matrix<uint8_t>(img->GetSizeX(), img->GetSizeY()));
    void *raw_pixels_matrix = img->GetMatrix();

    for (msize_t y = 0; y < img->GetSizeY(); y++)
    {
        for (msize_t x = 0; x < img->GetSizeX(); x++)
        {
            switch (img->GetPixelType())
            {
            case Pixel_Type::G:
            {
                Matrix<Pixel<Pixel_Type::G>> *pixels_g = reinterpret_cast<Matrix<Pixel<Pixel_Type::G>> *>(raw_pixels_matrix);

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * ((*pixels_g)[y][x].GetPixelValues().grey*(_red_weight + _green_weight + _blue_weight)/3);
                break;
            }
            case Pixel_Type::GA:
            {
                Matrix<Pixel<Pixel_Type::GA>> *pixels_ga = reinterpret_cast<Matrix<Pixel<Pixel_Type::GA>> *>(raw_pixels_matrix);
                struct Pixel_GA ga = (*pixels_ga)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * ((ga.grey + ga.alpha)*(_red_weight + _green_weight + _blue_weight)/3 / 2);
                break;
            }
            case Pixel_Type::RGB:
            {
                Matrix<Pixel<Pixel_Type::RGB>> *pixels_rgb = reinterpret_cast<Matrix<Pixel<Pixel_Type::RGB>> *>(raw_pixels_matrix);
                struct Pixel_RGB rgb = (*pixels_rgb)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * (rgb.red*_red_weight / 3 + rgb.green*_green_weight / 3 + rgb.blue*_blue_weight / 3);
                break;
            }
            case Pixel_Type::RGBA:
            {
                Matrix<Pixel<Pixel_Type::RGBA>> *pixels_rgba = reinterpret_cast<Matrix<Pixel<Pixel_Type::RGBA>> *>(raw_pixels_matrix);
                struct Pixel_RGBA rgba = (*pixels_rgba)[y][x].GetPixelValues();

                (*brightness_matrix)[y][x] = _negate*255 + (_negate ? -1 : 1) * (rgba.red*(_red_weight / 6) + rgba.green*(_green_weight / 6) + rgba.blue*(_blue_weight / 6) + rgba.alpha / 2);
                break;
            }
            default:
                throw AACException(error_codes::INVALID_PIXEL);
                break;
            }
        }
    }

    return brightness_matrix;
}

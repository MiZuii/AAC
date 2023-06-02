#include "../AAC.h"

/* -------------------------------------------------------------------------- */
/*                                AAC_BC_Simple                               */
/* -------------------------------------------------------------------------- */

AAC_BC_Simple::AAC_BC_Simple(float red_weight, float green_weight, float blue_weight, uint8_t negate) :
    _red_weight(red_weight), _green_weight(green_weight), _blue_weight(blue_weight), _negate(negate) {}

AAC_BC_Simple::AAC_BC_Simple() : AAC_BC_Simple::AAC_BC_Simple(1, 1, 1) {}

std::shared_ptr<AAC_Matrix<uint8_t>> AAC_BC_Simple::convert(AAC_Image* img) {
    std::shared_ptr<AAC_Matrix<uint8_t>> brightness_matrix(new AAC_Matrix<uint8_t>(img->size_x, img->size_y));
    void *raw_pixels_matrix = img->GetMatrix();

    for (unsigned int y = 0; y < img->size_y; y++)
    {
        for (unsigned int x = 0; x < img->size_x; x++)
        {
            switch (img->pixel_type)
            {
            case AAC_Pixel_Type::G:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>> *pixels_g = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>> *>(raw_pixels_matrix);

                brightness_matrix->GetElementReference(x, y) = _negate*255 + (_negate ? -1 : 1) * (pixels_g->GetElementReference(x, y).GetPixelValues().grey*(_red_weight + _green_weight + _blue_weight)/3);
                break;
            }
            case AAC_Pixel_Type::GA:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *pixels_ga = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *>(raw_pixels_matrix);
                struct AAC_Pixel_GA ga = pixels_ga->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = _negate*255 + (_negate ? -1 : 1) * ((ga.grey + ga.alpha)*(_red_weight + _green_weight + _blue_weight)/3 / 2);
                break;
            }
            case AAC_Pixel_Type::RGB:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *pixels_rgb = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *>(raw_pixels_matrix);
                struct AAC_Pixel_RGB rgb = pixels_rgb->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = _negate*255 + (_negate ? -1 : 1) * (rgb.red*_red_weight / 3 + rgb.green*_green_weight / 3 + rgb.blue*_blue_weight / 3);
                break;
            }
            case AAC_Pixel_Type::RGBA:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *pixels_rgba = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *>(raw_pixels_matrix);
                struct AAC_Pixel_RGBA rgba = pixels_rgba->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = _negate*255 + (_negate ? -1 : 1) * (rgba.red*(_red_weight / 6) + rgba.green*(_green_weight / 6) + rgba.blue*(_blue_weight / 6) + rgba.alpha / 2);
                break;
            }
            default:
                set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
                throw get_AAC_error_code();
                break;
            }
        }
    }

    return brightness_matrix;
}

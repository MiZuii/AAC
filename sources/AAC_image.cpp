#include "../AAC.h"

/**
 * @file AAC_image.cpp
 * @brief Contains the implementation of the AAC::Image class.
 */

/**
 * @brief Refactors the input data into a matrix of Pixel<G> elements.
 * @param size_x The size of the matrix in the x-axis.
 * @param size_y The size of the matrix in the y-axis.
 * @param data The input data.
 * @return A pointer to the matrix of Pixel<G> elements.
 */
AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>> *RefractorDataG(unsigned int size_x, unsigned int size_y, unsigned char *data)
{
    AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>> *arr = new AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            (*arr)[y][x].SetPixelValues(data[y * size_x + x]);
        }
    }

    return arr;
}

/**
 * @brief Refactors the input data into a matrix of Pixel<GA> elements.
 * @param size_x The size of the matrix in the x-axis.
 * @param size_y The size of the matrix in the y-axis.
 * @param n The number of color components per pixel.
 * @param data The input data.
 * @return A pointer to the matrix of Pixel<GA> elements.
 */
AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>> *RefractorDataGA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>> *arr = new AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            (*arr)[y][x].SetPixelValues(data[(y * size_x + x) * n], data[(y * size_x + x) * n + 1]);
        }
    }

    return arr;
}

/**
 * @brief Refactors the input data into a matrix of Pixel<RGB> elements.
 * @param size_x The size of the matrix in the x-axis.
 * @param size_y The size of the matrix in the y-axis.
 * @param n The number of color components per pixel.
 * @param data The input data.
 * @return A pointer to the matrix of Pixel<RGB> elements.
 */
AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>> *RefractorDataRGB(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>> *arr = new AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            (*arr)[y][x].SetPixelValues(data[(y * size_x + x) * n], data[(y * size_x + x) * n + 1], data[(y * size_x + x) * n + 2]);
        }
    }

    return arr;
}

/**
 * @brief Refactors the input data into a matrix of Pixel<RGBA> elements.
 * @param size_x The size of the matrix in the x-axis.
 * @param size_y The size of the matrix in the y-axis.
 * @param n The number of color components per pixel.
 * @param data The input data.
 * @return A pointer to the matrix of Pixel<RGBA> elements.
 */
AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>> *RefractorDataRGBA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>> *arr = new AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            size_t tmp = (y * size_x + x) * n;
            (*arr)[y][x].SetPixelValues(data[tmp], data[tmp + 1], data[tmp + 2], data[tmp + 3]);
        }
    }

    return arr;
}

/**
 * @brief Constructs an Image object with the specified parameters.
 * @param path The path to the image.
 * @param size_x The size of the image in the x-axis.
 * @param size_y The size of the image in the y-axis.
 * @param n The number of color components per pixel.
 * @param data The image data.
 */
AAC::Image::Image(std::string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) : _path(path), _n(n), pixel_type(static_cast<AAC::Pixel_Type>(n)), size_x(size_x), size_y(size_y)
{
    // check arguments validity
    if (size_x > MAX_SIZE || size_y > MAX_SIZE || n < 1 || n > 4 || !data)
    {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::INVALID_ARGUMENTS));
        throw AAC::get_error_code();
    }

    switch (pixel_type)
    {
    case AAC::Pixel_Type::G:
        _pixels_matrix = (void *)RefractorDataG(size_x, size_y, data);
        break;
    case AAC::Pixel_Type::GA:
        _pixels_matrix = (void *)RefractorDataGA(size_x, size_y, n, data);
        break;
    case AAC::Pixel_Type::RGB:
        _pixels_matrix = (void *)RefractorDataRGB(size_x, size_y, n, data);
        break;
    case AAC::Pixel_Type::RGBA:
        _pixels_matrix = (void *)RefractorDataRGBA(size_x, size_y, n, data);
        break;
    default:
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::INVALID_PIXEL));
        throw AAC::get_error_code();
        break;
    }
}

/**
 * @brief Destructor for the Image object.
 */
AAC::Image::~Image()
{
    switch (pixel_type)
    {
    case AAC::Pixel_Type::G:
        delete reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::G>> *>(_pixels_matrix);
        break;
    case AAC::Pixel_Type::GA:
        delete reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::GA>> *>(_pixels_matrix);
        break;
    case AAC::Pixel_Type::RGB:
        delete reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGB>> *>(_pixels_matrix);
        break;
    case AAC::Pixel_Type::RGBA:
        delete reinterpret_cast<AAC::Matrix<AAC::Pixel<AAC::Pixel_Type::RGBA>> *>(_pixels_matrix);
        break;
    default:
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::INVALID_PIXEL));
        throw AAC::get_error_code();
    }
}

/**
 * @brief Gets the matrix associated with the Image object.
 * @return A pointer to the matrix.
 */
void *AAC::Image::GetMatrix()
{
    return _pixels_matrix;
}

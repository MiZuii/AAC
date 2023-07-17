#include <aac.h>
#include <stb_image.h>

/**
 * @file aac_image.cpp
 * @brief Contains the implementation of the Image class.
 */

using namespace AAC;

/**
 * @brief Refactors the input data into a matrix of Pixel<G> elements.
 * @param size_x The size of the matrix in the x-axis.
 * @param size_y The size of the matrix in the y-axis.
 * @param data The input data.
 * @return A pointer to the matrix of Pixel<G> elements.
 */
Matrix<Pixel<Pixel_Type::G>> *RefractorDataG(msize_t size_x, msize_t size_y, unsigned char *data) {
    Matrix<Pixel<Pixel_Type::G>> *arr = new Matrix<Pixel<Pixel_Type::G>>(size_x, size_y);

    for (msize_t y = 0; y < size_y; y++)
    {
        for (msize_t x = 0; x < size_x; x++)
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
Matrix<Pixel<Pixel_Type::GA>> *RefractorDataGA(msize_t size_x, msize_t size_y, uint8_t n, unsigned char *data) {
    Matrix<Pixel<Pixel_Type::GA>> *arr = new Matrix<Pixel<Pixel_Type::GA>>(size_x, size_y);

    for (msize_t y = 0; y < size_y; y++)
    {
        for (msize_t x = 0; x < size_x; x++)
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
Matrix<Pixel<Pixel_Type::RGB>> *RefractorDataRGB(msize_t size_x, msize_t size_y, uint8_t n, unsigned char *data) {
    Matrix<Pixel<Pixel_Type::RGB>> *arr = new Matrix<Pixel<Pixel_Type::RGB>>(size_x, size_y);

    for (msize_t y = 0; y < size_y; y++)
    {
        for (msize_t x = 0; x < size_x; x++)
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
Matrix<Pixel<Pixel_Type::RGBA>> *RefractorDataRGBA(msize_t size_x, msize_t size_y, uint8_t n, unsigned char *data) {
    Matrix<Pixel<Pixel_Type::RGBA>> *arr = new Matrix<Pixel<Pixel_Type::RGBA>>(size_x, size_y);

    for (msize_t y = 0; y < size_y; y++)
    {
        for (msize_t x = 0; x < size_x; x++)
        {
            size_t tmp = (y * size_x + x) * n;
            (*arr)[y][x].SetPixelValues(data[tmp], data[tmp + 1], data[tmp + 2], data[tmp + 3]);
        }
    }

    return arr;
}

/**
 * @brief Constructs an Image object with the specified parameters.
 * @param size_x The size of the image in the x-axis.
 * @param size_y The size of the image in the y-axis.
 * @param n The number of color components per pixel.
 * @param data The image data.
 */
Image::Image(msize_t size_x, msize_t size_y, uint8_t n, unsigned char *data) : _n(n), _pixel_type(static_cast<Pixel_Type>(n)), _size_x(size_x), _size_y(size_y) {
    // check arguments validity
    if (_size_x > MAX_SIZE || _size_y > MAX_SIZE || _n < 1 || _n > 4 || !data) {
        throw AACException(error_codes::INVALID_ARGUMENTS);
    }

    switch (_pixel_type) {
        case Pixel_Type::G:
            _pixels_matrix = (void *)RefractorDataG(_size_x, _size_y, data);
            break;
        case Pixel_Type::GA:
            _pixels_matrix = (void *)RefractorDataGA(_size_x, _size_y, _n, data);
            break;
        case Pixel_Type::RGB:
            _pixels_matrix = (void *)RefractorDataRGB(_size_x, _size_y, _n, data);
            break;
        case Pixel_Type::RGBA:
            _pixels_matrix = (void *)RefractorDataRGBA(_size_x, _size_y, _n, data);
            break;
        default:
            throw AACException(error_codes::INVALID_PIXEL);
            break;
    }
}

/**
 * @brief Constructs an Image object with the specified parameters.
 * @param path Path to an image to open.
 */
Image::Image(std::string path) {

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);
    _size_x = x;
    _size_y = y;
    _n = n;
    _pixel_type = static_cast<Pixel_Type>(_n);

    if (!data) {
        throw AACException(error_codes::IMAGE_OPEN_FAIL);
    }

    if (_size_x > MAX_SIZE || _size_y > MAX_SIZE || _n < 1 || _n > 4) {
        throw AACException(error_codes::INVALID_ARGUMENTS);
    }

    switch (_pixel_type) {
        case Pixel_Type::G:
            _pixels_matrix = (void *)RefractorDataG(_size_x, _size_y, data);
            break;
        case Pixel_Type::GA:
            _pixels_matrix = (void *)RefractorDataGA(_size_x, _size_y, _n, data);
            break;
        case Pixel_Type::RGB:
            _pixels_matrix = (void *)RefractorDataRGB(_size_x, _size_y, _n, data);
            break;
        case Pixel_Type::RGBA:
            _pixels_matrix = (void *)RefractorDataRGBA(_size_x, _size_y, _n, data);
            break;
        default:
            throw AACException(error_codes::INVALID_PIXEL);
            break;
    }

    free(data);
}

/**
 * @brief Destructor for the Image object.
 */
Image::~Image() {
    switch (_pixel_type)
    {
    case Pixel_Type::G:
        delete reinterpret_cast<Matrix<Pixel<Pixel_Type::G>> *>(_pixels_matrix);
        break;
    case Pixel_Type::GA:
        delete reinterpret_cast<Matrix<Pixel<Pixel_Type::GA>> *>(_pixels_matrix);
        break;
    case Pixel_Type::RGB:
        delete reinterpret_cast<Matrix<Pixel<Pixel_Type::RGB>> *>(_pixels_matrix);
        break;
    case Pixel_Type::RGBA:
        delete reinterpret_cast<Matrix<Pixel<Pixel_Type::RGBA>> *>(_pixels_matrix);
        break;
    default:
        break;
    }
}

/**
 * @brief Gets the matrix associated with the Image object.
 * @return A pointer to the matrix.
 */
void *Image::GetMatrix() {
    return _pixels_matrix;
}

/**
 * @brief Getter for size_x member.
 * 
 * @return the size.
 */
msize_t Image::GetSizeX() const {
    return _size_x;
}

/**
 * @brief Getter for size_y member.
 * 
 * @return the size.
 */
msize_t Image::GetSizeY() const {
    return _size_y;
}

/**
 * @brief Getter for pixel_type member.
 * 
 * @return the size.
 */
Pixel_Type Image::GetPixelType() const {
    return _pixel_type;
}

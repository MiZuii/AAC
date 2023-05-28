#include "../AAC.h"

AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>> *RefractorDataG(unsigned int size_x, unsigned int size_y, unsigned char *data)
{
    AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>> *arr = new AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            arr->GetElementReference(x, y).SetPixelValues(data[y * size_x + x]);
        }
    }

    return arr;
}

AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *RefractorDataGA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *arr = new AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            arr->GetElementReference(x, y).SetPixelValues(data[(y * size_x + x) * n], data[(y * size_x + x) * n + 1]);
        }
    }

    return arr;
}

AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *RefractorDataRGB(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *arr = new AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            arr->GetElementReference(x, y).SetPixelValues(data[(y * size_x + x) * n], data[(y * size_x + x) * n + 1], data[(y * size_x + x) * n + 2]);
        }
    }

    return arr;
}

AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *RefractorDataRGBA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data)
{
    AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *arr = new AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>>(size_x, size_y);

    for (unsigned int y = 0; y < size_y; y++)
    {
        for (unsigned int x = 0; x < size_x; x++)
        {
            size_t tmp = (y * size_x + x) * n;
            arr->GetElementReference(x, y).SetPixelValues(data[tmp], data[tmp+ 1], data[tmp + 2], data[tmp + 3]);
        }
    }

    return arr;
}

AAC_Image::AAC_Image(std::string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) : _path(path), _n(n), pixel_type(static_cast<AAC_Pixel_Type>(n)), size_x(size_x), size_y(size_y)
{
    // check arguments validity
    if (size_x > MAX_SIZE || size_y > MAX_SIZE || n < 1 || n > 4 || !data)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    switch (pixel_type)
    {
    case AAC_Pixel_Type::G:
        _pixels_matrix = (void *)RefractorDataG(size_x, size_y, data);
        break;
    case AAC_Pixel_Type::GA:
        _pixels_matrix = (void *)RefractorDataGA(size_x, size_y, n, data);
        break;
    case AAC_Pixel_Type::RGB:
        _pixels_matrix = (void *)RefractorDataRGB(size_x, size_y, n, data);
        break;
    case AAC_Pixel_Type::RGBA:
        _pixels_matrix = (void *)RefractorDataRGBA(size_x, size_y, n, data);
        break;
    default:
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
        break;
    }
}

AAC_Image::~AAC_Image()
{
    switch (pixel_type)
    {
    case AAC_Pixel_Type::G:
        delete reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::G>> *>(_pixels_matrix);
        break;
    case AAC_Pixel_Type::GA:
        delete reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *>(_pixels_matrix);
        break;
    case AAC_Pixel_Type::RGB:
        delete reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *>(_pixels_matrix);
        break;
    case AAC_Pixel_Type::RGBA:
        delete reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *>(_pixels_matrix);
        break;
    default:
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }
}

void *AAC_Image::GetMatrix()
{
    return _pixels_matrix;
}
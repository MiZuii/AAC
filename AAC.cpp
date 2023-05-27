//
// Created by Pedro on 13.03.2023.
//

#include "AAC.h"
#include <iostream>
#include <string>

// library import for reading image format files
#define CUSTOM_FOPEN_LOAD
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_SIZE 4000

using namespace std;

/* -------------------------------------------------------------------------- */
/*                                 ERROR CODES                                */
/* -------------------------------------------------------------------------- */

std::unique_ptr<int> cipka = std::make_unique<int>();
std::shared_ptr<int> chuj = std::shared_ptr<int>();
void set_AAC_error_code(std::error_code ec)
{
    AAC_error_code = ec;
}

std::error_code get_AAC_error_code()
{
    return AAC_error_code;
}

void clear_AAC_error_code()
{
    AAC_error_code = std::error_code{};
}

std::error_code make_error_code(AAC_error_codes ec)
{
    return std::error_code{static_cast<int>(ec), AAC_category};
}

/* -------------------------------------------------------------------------- */
/*                                MATRIX CLASS                                */
/* -------------------------------------------------------------------------- */

template <typename T>
AAC_Matrix<T>::AAC_Matrix(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y)
{
    _matrix = new T *[size_y];
    if (NULL == _matrix)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
        throw get_AAC_error_code();
    }

    for (unsigned int i = 0; i < size_y; i++)
    {
        _matrix[i] = new T[size_x];

        if (NULL == _matrix[i])
        {
            set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
            throw get_AAC_error_code();
        }
    }
}

template <typename T>
AAC_Matrix<T>::~AAC_Matrix()
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

template <typename T>
const T AAC_Matrix<T>::GetElement(unsigned int x, unsigned int y)
{
    if (x >= size_x || y >= size_y)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw get_AAC_error_code();
    }
    return _matrix[y][x];
}

template <typename T>
T &AAC_Matrix<T>::GetElementReference(unsigned int x, unsigned int y)
{
    if (x >= size_x || y >= size_y)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw get_AAC_error_code();
    }
    return _matrix[y][x];
}

template <typename T>
unsigned int AAC_Matrix<T>::GetXSize() {
    return size_x;
}

template <typename T>
unsigned int AAC_Matrix<T>::GetYSize() {
    return size_y;
}

/* -------------------------------------------------------------------------- */
/*                                 PIXEL CLASS                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------- GREY TYPE ------------------------------- */
template <>
class AAC_Pixel<AAC_Pixel_Type::G>
{
private:
    AAC_Pixel_G _pixel_values;

public:
    // constructors
    AAC_Pixel();
    AAC_Pixel(uint8_t grey);

    // getters and setters
    struct AAC_Pixel_G GetPixelValues();
    void SetPixelValues(uint8_t grey);
};

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
/* ------------------------------ GREY TYPE END ----------------------------- */

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */
template <>
class AAC_Pixel<AAC_Pixel_Type::GA>
{
private:
    AAC_Pixel_GA _pixel_values;

public:
    // constructors
    AAC_Pixel();
    AAC_Pixel(uint8_t grey, uint8_t alpha);

    // getters and setters
    struct AAC_Pixel_GA GetPixelValues();
    void SetPixelValues(uint8_t grey, uint8_t alpha);
};

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
/* --------------------------- GREY ALPHA TYPE END -------------------------- */

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */
template <>
class AAC_Pixel<AAC_Pixel_Type::RGB>
{
private:
    AAC_Pixel_RGB _pixel_values;

public:
    // constructors
    AAC_Pixel();
    AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue);

    // getters and setters
    struct AAC_Pixel_RGB GetPixelValues();
    void SetPixelValues(uint8_t red, uint8_t green, uint8_t blue);
};

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
/* ------------------------- RED GREEN BLUE TYPE END ------------------------ */

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */
template <>
class AAC_Pixel<AAC_Pixel_Type::RGBA>
{
private:
    AAC_Pixel_RGBA _pixel_values;

public:
    // constructors
    AAC_Pixel();
    AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    // getters and setters
    struct AAC_Pixel_RGBA GetPixelValues();
    void SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
};

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

void
AAC_Pixel<AAC_Pixel_Type::RGBA>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}
/* ---------------------- RED GREEN BLUE ALPHA TYPE END --------------------- */

template <>
class AAC_Pixel<AAC_Pixel_Type::EMPTY>
{
private:
    AAC_Pixel_EMPTY _pixel_values;

public:
    AAC_Pixel();
};

AAC_Pixel<AAC_Pixel_Type::EMPTY>::AAC_Pixel()
{
    // empty for now
}

/* -------------------------------------------------------------------------- */
/*                                 IMAGE CLASS                                */
/* -------------------------------------------------------------------------- */

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

AAC_Image::AAC_Image(string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) : _path(path), _n(n), pixel_type(static_cast<AAC_Pixel_Type>(n)), size_x(size_x), size_y(size_y)
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
        break;
    }
}

void *AAC_Image::GetMatrix()
{
    return _pixels_matrix;
}

/* -------------------------------------------------------------------------- */
/*                             GLOBAL IMAGE OPENER                            */
/* -------------------------------------------------------------------------- */
AAC_Image *AAC_OpenImage(std::string path)
{

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

    if (!data)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }
    else {
        AAC_Image* opened_image = new AAC_Image(path, x, y, n, data);
        free(data);
        return opened_image;
    }
}

/* -------------------------------------------------------------------------- */
/*                                 CHUNK CLASS                                */
/* -------------------------------------------------------------------------- */

AAC_Chunk::AAC_Chunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, AAC_Matrix<uint8_t> *data) : _X_start_index(X_start_index), _X_end_index(X_end_index), _Y_start_index(Y_start_index), _Y_end_index(Y_end_index), _data(data) {}

AAC_Chunk::AAC_Chunk() : AAC_Chunk(0, 0, 0, 0, NULL) {};

void AAC_Chunk::SetChunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, AAC_Matrix<uint8_t> *data)
{
    _X_start_index = X_start_index;
    _X_end_index = X_end_index;
    _Y_start_index = Y_start_index;
    _Y_end_index = Y_end_index;
    _data = data;
}

AAC_Matrix<uint8_t>*  AAC_Chunk::GetData() {
    return _data;
}

unsigned int AAC_Chunk::GetXStart() {
    return _X_start_index;
}

unsigned int AAC_Chunk::GetYStart() {
    return _Y_start_index;
}

unsigned int AAC_Chunk::GetXEnd() {
    return _X_end_index;
}

unsigned int AAC_Chunk::GetYEnd() {
    return _Y_end_index;
}

/* -------------------------------------------------------------------------- */
/*                               CONVERTER CLASS                              */
/* -------------------------------------------------------------------------- */

const float AAC_Converter::_ratio = 0.45;

AAC_Converter::AAC_Converter(AAC_BrightnessFunction bf, AAC_ChunkConvertFunction cc) : _brightness_func(bf), _chunk_convertion_func(cc) {};

AAC_Matrix<AAC_Chunk>* AAC_Converter::generateChunks(AAC_Image *img, unsigned int chunk_size, AAC_Matrix<uint8_t>* brightness_matrix) {

    if( NULL == brightness_matrix || NULL == img ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    unsigned int x_nof_chunks = img->size_x / chunk_size;
    unsigned int lcols_to_cut = (img->size_x - chunk_size * x_nof_chunks) / 2;

    unsigned int y_chunk_size = (unsigned int)((float)chunk_size / _ratio);
    unsigned int y_nof_chunks = img->size_y / y_chunk_size;
    unsigned int urows_to_cut = (img->size_y - y_chunk_size * y_nof_chunks) / 2;

    AAC_Matrix<AAC_Chunk>* arr = new AAC_Matrix<AAC_Chunk>(x_nof_chunks, y_nof_chunks);

    for (unsigned int i = 0; i < y_nof_chunks; i++)
    {
        for (unsigned int j = 0; j < x_nof_chunks; j++)
        {
            arr->GetElementReference(j, i).SetChunk(lcols_to_cut + j * chunk_size,
                                                   lcols_to_cut + (j + 1) * chunk_size,
                                                   urows_to_cut + i * y_chunk_size,
                                                   urows_to_cut + (i + 1) * y_chunk_size,
                                                   brightness_matrix);
        }
    }

    return arr;
}

std::string AAC_Converter::CreateArt(AAC_Image* img, AAC_Conversion_Options options) {

    if( NULL == img ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    AAC_Matrix<uint8_t>* brightness_m = _brightness_func(img);
    AAC_Matrix<AAC_Chunk>* chunked_image = generateChunks(img, options.chunk_size, brightness_m);
    std::string art = _chunk_convertion_func(chunked_image, options);
    delete brightness_m;
    delete chunked_image;
    return art;
}

/* -------------------------------------------------------------------------- */
/*                            BRIGHTNESS FUNCTIONS                            */
/* -------------------------------------------------------------------------- */

AAC_Matrix<uint8_t> *AAC_bf_SimpleAverage(AAC_Image *img)
{
    AAC_Matrix<uint8_t> *brightness_matrix = new AAC_Matrix<uint8_t>(img->size_x, img->size_y);
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

                brightness_matrix->GetElementReference(x, y) = pixels_g->GetElementReference(x, y).GetPixelValues().grey;
                break;
            }
            case AAC_Pixel_Type::GA:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *pixels_ga = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::GA>> *>(raw_pixels_matrix);
                struct AAC_Pixel_GA ga = pixels_ga->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = (ga.grey + ga.alpha) / 2;
                break;
            }
            case AAC_Pixel_Type::RGB:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *pixels_rgb = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGB>> *>(raw_pixels_matrix);
                struct AAC_Pixel_RGB rgb = pixels_rgb->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = rgb.red / 3 + rgb.green / 3 + rgb.blue / 3;
                break;
            }
            case AAC_Pixel_Type::RGBA:
            {
                AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *pixels_rgba = reinterpret_cast<AAC_Matrix<AAC_Pixel<AAC_Pixel_Type::RGBA>> *>(raw_pixels_matrix);
                struct AAC_Pixel_RGBA rgba = pixels_rgba->GetElementReference(x, y).GetPixelValues();

                brightness_matrix->GetElementReference(x, y) = rgba.red / 6 + rgba.green / 6 + rgba.blue / 6 + rgba.alpha / 2;
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

/* -------------------------------------------------------------------------- */
/*                         CHUNK CONVERSION FUNCTIONS                         */
/* -------------------------------------------------------------------------- */


uint8_t get_char_index(size_t interval_length, uint8_t brightness) {
    return brightness / interval_length;
}


std::string AAC_cc_Simple(AAC_Matrix<AAC_Chunk>* chunks, struct AAC_Conversion_Options options)
{

    // find the interval of the alphabet
    size_t alphabet_len = options.alphabet.length();

    if( alphabet_len < 2 || alphabet_len > 255 ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    uint8_t interval_len = 255 / alphabet_len;


    // make resulting char matrix and gather chunk data
    AAC_Matrix<char> art_result = AAC_Matrix<char>(chunks->GetXSize(), chunks->GetYSize());
    AAC_Matrix<uint8_t>* brightness_matrix = chunks->GetElementReference(0, 0).GetData();


    // iterate through chunks and generate resultsize_t x = 0; x < chunks.GetXSize(); x++
    for(size_t y = 0; y < chunks->GetYSize(); y++) {
        for(size_t x = 0; x < chunks->GetXSize(); x++) {

            // divide into edge chunks and middle chunks
            if( 0 == x || 0 == y || chunks->GetXSize() - 1 == x || chunks->GetYSize() - 1 == y ) {
                // edge chunk
                // calculate average of brightness of the chunk

                AAC_Chunk cchunk = chunks->GetElement(x, y);

                unsigned long sum = 0;
                unsigned long quantity = (cchunk.GetYEnd() - cchunk.GetYStart())*(cchunk.GetYEnd() - cchunk.GetYStart());

                for(size_t cy = cchunk.GetYStart(); cy < cchunk.GetYEnd(); cy++) {
                    for(size_t cx = cchunk.GetXStart(); cx < cchunk.GetXEnd(); cx++) {
                        sum += brightness_matrix->GetElement(cx, cy);
                    }
                }

                art_result.GetElementReference(x, y) = options.alphabet[get_char_index(interval_len, sum / quantity)];

            }
            else {
                // middle chunk
                /*   REPEATED FOR NOW   */
                // edge chunk
                // calculate average of brightness of the chunk

                AAC_Chunk cchunk = chunks->GetElement(x, y);

                unsigned long sum = 0;
                unsigned long quantity = (cchunk.GetYEnd() - cchunk.GetYStart())*(cchunk.GetYEnd() - cchunk.GetYStart());

                for(size_t cy = cchunk.GetYStart(); cy < cchunk.GetYEnd(); cy++) {
                    for(size_t cx = cchunk.GetXStart(); cx < cchunk.GetXEnd(); cx++) {
                        sum += brightness_matrix->GetElement(cx, cy);
                    }
                }

                art_result.GetElementReference(x, y) = options.alphabet[get_char_index(interval_len, sum / quantity)];
            }
        }
    }

    std::string result = "";

    // conver to final string
    for(size_t y = 0; y < art_result.GetYSize(); y++) {
        for(size_t x = 0; x < art_result.GetXSize(); x++) {

            result.push_back(art_result.GetElement(x, y));
        }
        result += '\n';
    }

    return result;
}

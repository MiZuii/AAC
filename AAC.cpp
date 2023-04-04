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


void set_AAC_error_code(std::error_code ec) {
  AAC_error_code = ec;
}

std::error_code get_AAC_error_code() {
  return AAC_error_code;
}

void clear_AAC_error_code() {
  AAC_error_code = std::error_code{};
}

std::error_code make_error_code(AAC_error_codes ec) {
  return std::error_code{static_cast<int>(ec), AAC_category};
}

/* -------------------------------------------------------------------------- */
/*                                 PIXEL CLASS                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------- GREY TYPE ------------------------------- */
template<>
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

AAC_Pixel<AAC_Pixel_Type::G>::AAC_Pixel(uint8_t grey) {
    _pixel_values.grey = grey;
}

AAC_Pixel<AAC_Pixel_Type::G>::AAC_Pixel() : AAC_Pixel(0) {}

struct AAC_Pixel_G AAC_Pixel<AAC_Pixel_Type::G>::GetPixelValues()
{
    return _pixel_values;
}

void AAC_Pixel<AAC_Pixel_Type::G>::SetPixelValues(uint8_t grey) {
    _pixel_values.grey = grey;
}
/* ------------------------------ GREY TYPE END ----------------------------- */

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */
template<>
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

AAC_Pixel<AAC_Pixel_Type::GA>::AAC_Pixel(uint8_t grey, uint8_t alpha) {
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}

AAC_Pixel<AAC_Pixel_Type::GA>::AAC_Pixel() : AAC_Pixel(0, 0) {}

struct AAC_Pixel_GA AAC_Pixel<AAC_Pixel_Type::GA>::GetPixelValues()
{
    return _pixel_values;
}

void AAC_Pixel<AAC_Pixel_Type::GA>::SetPixelValues(uint8_t grey, uint8_t alpha) {
    _pixel_values.grey = grey;
    _pixel_values.alpha = alpha;
}
/* --------------------------- GREY ALPHA TYPE END -------------------------- */

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */
template<>
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

AAC_Pixel<AAC_Pixel_Type::RGB>::AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue) {
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}

AAC_Pixel<AAC_Pixel_Type::RGB>::AAC_Pixel() : AAC_Pixel(0, 0, 0) {}

struct AAC_Pixel_RGB AAC_Pixel<AAC_Pixel_Type::RGB>::GetPixelValues()
{
    return _pixel_values;
}

void AAC_Pixel<AAC_Pixel_Type::RGB>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue) {
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
}
/* ------------------------- RED GREEN BLUE TYPE END ------------------------ */

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */
template<>
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

AAC_Pixel<AAC_Pixel_Type::RGBA>::AAC_Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
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

void AAC_Pixel<AAC_Pixel_Type::RGBA>::SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    _pixel_values.red = red;
    _pixel_values.green = green;
    _pixel_values.blue = blue;
    _pixel_values.alpha = alpha;
}
/* ---------------------- RED GREEN BLUE ALPHA TYPE END --------------------- */


template<>
class AAC_Pixel<AAC_Pixel_Type::EMPTY>
{
private:
    AAC_Pixel_EMPTY _pixel_values;

public:
    AAC_Pixel();
};

AAC_Pixel<AAC_Pixel_Type::EMPTY>::AAC_Pixel() {
    // empty for now
}


/* -------------------------------------------------------------------------- */
/*                                 IMAGE CLASS                                */
/* -------------------------------------------------------------------------- */

AAC_Pixel<AAC_Pixel_Type::G>** RefractorDataG(unsigned int size_x, unsigned int size_y, unsigned char *data) {
    AAC_Pixel<AAC_Pixel_Type::G> **arr; 
    arr = (AAC_Pixel<AAC_Pixel_Type::G>**)malloc(sizeof(AAC_Pixel<AAC_Pixel_Type::G>*)*size_x*size_y);

    if( NULL == arr )
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }

    for(unsigned int y = 0; y < size_y; y++) {
        for(unsigned int x = 0; x < size_x; x++)
        {
            uint8_t grey = data[y*size_x + x];
            arr[y*size_x + x] = new AAC_Pixel<AAC_Pixel_Type::G>(grey);
        }
    }

    return arr;
}

AAC_Pixel<AAC_Pixel_Type::GA>** RefractorDataGA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) {
    AAC_Pixel<AAC_Pixel_Type::GA> **arr; 
    arr = (AAC_Pixel<AAC_Pixel_Type::GA>**)malloc(sizeof(AAC_Pixel<AAC_Pixel_Type::GA>*)*size_x*size_y);

    if( NULL == arr )
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }

    for(unsigned int y = 0; y < size_y; y++) {
        for(unsigned int x = 0; x < size_x; x++)
        {
            uint8_t grey = data[(y*size_x + x)*n];
            uint8_t alpha = data[(y*size_x + x)*n + 1];
            arr[y*size_x + x] = new AAC_Pixel<AAC_Pixel_Type::GA>(grey, alpha);
        }
    }

    return arr;
}

AAC_Pixel<AAC_Pixel_Type::RGB>** RefractorDataRGB(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) {
    AAC_Pixel<AAC_Pixel_Type::RGB> **arr; 
    arr = (AAC_Pixel<AAC_Pixel_Type::RGB>**)malloc(sizeof(AAC_Pixel<AAC_Pixel_Type::RGB>*)*size_x*size_y);

    if( NULL == arr )
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }

    for(unsigned int y = 0; y < size_y; y++) {
        for(unsigned int x = 0; x < size_x; x++)
        {
            uint8_t red = data[(y*size_x + x)*n];
            uint8_t green = data[(y*size_x + x)*n + 1];
            uint8_t blue = data[(y*size_x + x)*n + 2];
            arr[y*size_x + x] = new AAC_Pixel<AAC_Pixel_Type::RGB>(red, green, blue);
        }
    }

    return arr;
}

AAC_Pixel<AAC_Pixel_Type::RGBA>** RefractorDataRGBA(unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) {
    AAC_Pixel<AAC_Pixel_Type::RGBA> **arr; 
    arr = (AAC_Pixel<AAC_Pixel_Type::RGBA>**)malloc(sizeof(AAC_Pixel<AAC_Pixel_Type::RGBA>*)*size_x*size_y);

    if( NULL == arr )
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }

    for(unsigned int y = 0; y < size_y; y++) {
        for(unsigned int x = 0; x < size_x; x++)
        {
            uint8_t red = data[(y*size_x + x)*n];
            uint8_t green = data[(y*size_x + x)*n + 1];
            uint8_t blue = data[(y*size_x + x)*n + 2];
            uint8_t alpha = data[(y*size_x + x)*n + 3];
            arr[y*size_x + x] = new AAC_Pixel<AAC_Pixel_Type::RGBA>(red, green, blue, alpha);
        }
    }

    return arr;
}


AAC_Image::AAC_Image(string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data) : 
    _path(path), _n(n), pixel_type(static_cast<AAC_Pixel_Type>(n)), size_x(size_x), size_y(size_y)
{
    // check arguments validity
    if(size_x > MAX_SIZE || size_y > MAX_SIZE || n < 1 || n > 4 || !data) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    switch (pixel_type)
    {
    case AAC_Pixel_Type::G:
        _pixels = (void **)RefractorDataG(size_x, size_y, data);
        break;
    case AAC_Pixel_Type::GA:
        _pixels = (void **)RefractorDataGA(size_x, size_y, n, data);
        break;
    case AAC_Pixel_Type::RGB:
        _pixels = (void **)RefractorDataRGB(size_x, size_y, n, data);
        break;
    case AAC_Pixel_Type::RGBA:
        _pixels = (void **)RefractorDataRGBA(size_x, size_y, n, data);
        break;
    default:
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
        break;
    }
}

AAC_Image::~AAC_Image() {
    for(unsigned long int i = 0; i<size_x*size_y; i++) {
        switch (pixel_type)
        {
        case AAC_Pixel_Type::G:
            delete static_cast<AAC_Pixel<AAC_Pixel_Type::G>*>(_pixels[i]);
            break;
        case AAC_Pixel_Type::GA:
            delete static_cast<AAC_Pixel<AAC_Pixel_Type::GA>*>(_pixels[i]);
            break;
        case AAC_Pixel_Type::RGB:
            delete static_cast<AAC_Pixel<AAC_Pixel_Type::RGB>*>(_pixels[i]);
            break;
        case AAC_Pixel_Type::RGBA:
            delete static_cast<AAC_Pixel<AAC_Pixel_Type::RGBA>*>(_pixels[i]);
            break;
        default:
            set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
            throw get_AAC_error_code();
            break;
        }
    }
    free(_pixels);
}

void *AAC_Image::GetPixel(unsigned int x, unsigned int y) {
    return _pixels[y*size_x+x];
}

/* -------------------------------------------------------------------------- */
/*                             GLOBAL IMAGE OPENER                            */
/* -------------------------------------------------------------------------- */
AAC_Image *AAC_OpenImage(std::string path) {

    int x,y,n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

    if(!data) 
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }
    else
    {
        return new AAC_Image("test.jpg", x, y, n, data);
    }
}

/* -------------------------------------------------------------------------- */
/*                                 CHUNK CLASS                                */
/* -------------------------------------------------------------------------- */

AAC_Chunk::AAC_Chunk(unsigned int _X_start_index, unsigned int _X_end_index, unsigned int _Y_start_index, unsigned int _Y_end_index, uint8_t *data) :
    _X_start_index(_X_start_index), _X_end_index(_X_end_index), _Y_start_index(_Y_start_index), _Y_end_index(_Y_end_index), _data(data) {}

/* -------------------------------------------------------------------------- */
/*                                MATRIX CLASS                                */
/* -------------------------------------------------------------------------- */

template<typename T>
AAC_Matrix<T>::AAC_Matrix(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y)
{
    _matrix = (T**)malloc(sizeof(T*) * size_y);
    if( NULL == _matrix )
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
        throw get_AAC_error_code();
    }

    for(unsigned int i=0; i<size_y; i++)
    {
        _matrix[i] = (T*)malloc(sizeof(T) * size_x);

        if( NULL == _matrix[i] )
        {
            set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
            throw get_AAC_error_code();
        }
    }
}

template<typename T>
AAC_Matrix<T>::~AAC_Matrix()
{
    for(unsigned int i=0; i<size_y; i++)
    {
        for(unsigned int j=0; j<size_x; j++)
        {
            try
            {
                delete _matrix[i][j];
            }
            catch(const std::exception& e)
            {
                continue;
            }
        }
        free(_matrix[i]);
    }
    free(_matrix);
}

template<typename T>
void AAC_Matrix<T>::SetElement(unsigned int x, unsigned int y, T element)
{
    _matrix[y][x] = element;
}

template<typename T>
T AAC_Matrix<T>::GetElement(unsigned int x, unsigned int y){
    return _matrix[y][x];
}

/* -------------------------------------------------------------------------- */
/*                               CONVERTER CLASS                              */
/* -------------------------------------------------------------------------- */

const float AAC_Converter::_ratio = 0.45;

AAC_Converter::AAC_Converter(AAC_BrightnessFunction bf, AAC_ChunkConvertFunction cc) : 
    _brightness_func(bf), _chunk_convertion_func(cc) {}

AAC_Matrix<AAC_Chunk*> AAC_Converter::generateChunks(unsigned int img_x, unsigned int img_y, unsigned int chunk_size, uint8_t *data)
{
    unsigned int x_nof_chunks = img_x / chunk_size;
    unsigned int lcols_to_cut = (img_x - chunk_size*x_nof_chunks)/2;

    unsigned int y_chunk_size = (unsigned int)((float)chunk_size * _ratio);
    unsigned int y_nof_chunks = img_y / y_chunk_size;
    unsigned int urows_to_cut = (img_y - y_chunk_size*y_nof_chunks)/2;

    AAC_Matrix<AAC_Chunk*> arr = AAC_Matrix<AAC_Chunk*>(x_nof_chunks, y_nof_chunks);

    for(unsigned int i=0; i<y_nof_chunks; i++)
    {
        for(unsigned int j=0; j<x_nof_chunks; j++)
        {
            arr.SetElement(j, i, new AAC_Chunk(lcols_to_cut+j*chunk_size,
                                               lcols_to_cut+(j+1)*chunk_size,
                                               urows_to_cut+i*y_chunk_size,
                                               urows_to_cut+(i+1)*y_chunk_size, data));
        }
    }

    return arr;
}

/* -------------------------------------------------------------------------- */
/*                            BRIGHTNESS FUNCTIONS                            */
/* -------------------------------------------------------------------------- */

uint8_t *AAC_bf_SimpleAverage(AAC_Image img) {
    uint8_t *brightness_array = (uint8_t*)malloc(sizeof(uint8_t)*img.size_x*img.size_y);

    struct AAC_Pixel_GA tmp_ga;
    struct AAC_Pixel_RGB tmp_rgb;
    struct AAC_Pixel_RGBA tmp_rgba;

    for(unsigned long i=0; i<img.size_x*img.size_y; i++) 
    {
        switch (img.pixel_type)
        {
        case AAC_Pixel_Type::G:
            brightness_array[i] = ((AAC_Pixel<AAC_Pixel_Type::G>*)img.GetPixel(i%img.size_x, i/img.size_y))->GetPixelValues().grey;
            break;

        case AAC_Pixel_Type::GA:
            tmp_ga = ((AAC_Pixel<AAC_Pixel_Type::GA>*)img.GetPixel(i%img.size_x, i/img.size_y))->GetPixelValues();
            brightness_array[i] = (tmp_ga.grey + tmp_ga.alpha)/2;
            break;

        case AAC_Pixel_Type::RGB:
            tmp_rgb = ((AAC_Pixel<AAC_Pixel_Type::RGB>*)img.GetPixel(i%img.size_x, i/img.size_y))->GetPixelValues();
            brightness_array[i] = (tmp_rgb.red + tmp_rgb.green + tmp_rgb.blue)/3;
            break;

        case AAC_Pixel_Type::RGBA:
            tmp_rgba = ((AAC_Pixel<AAC_Pixel_Type::RGBA>*)img.GetPixel(i%img.size_x, i/img.size_y))->GetPixelValues();
            brightness_array[i] = (tmp_rgba.red + tmp_rgba.green + tmp_rgba.blue + 3*tmp_rgba.alpha)/6;
            break;
        
        default:
            set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
            throw get_AAC_error_code();
            break;
        }
    }

    return brightness_array;
}

/* -------------------------------------------------------------------------- */
/*                         CHUNK CONVERSION FUNCTIONS                         */
/* -------------------------------------------------------------------------- */

char AAC_cc_Simple(AAC_Chunk chunk) {
    // yet to be implemented
    return 'X';
}

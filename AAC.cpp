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
    _path(path), _size_x(size_x), _size_y(size_y), _n(n), pixel_type(static_cast<AAC_Pixel_Type>(n))
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
    for(unsigned long int i = 0; i<_size_x*_size_y; i++) {
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

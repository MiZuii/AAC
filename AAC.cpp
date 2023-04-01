//
// Created by Pedro on 13.03.2023.
//

#include "AAC.h"
#include <iostream>
#include <string>

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

template<>
class AAC_Pixel<AAC_Pixel_Type::G>
{
private:
    AAC_Pixel_G _pixel_values;

public:
    AAC_Pixel();
    struct AAC_Pixel_G GetPixelValues();
    void SetPixelValues();

};

AAC_Pixel<AAC_Pixel_Type::G>::AAC_Pixel() {
    AAC_Pixel<AAC_Pixel_Type::G>::_pixel_values.grey = 0;
}

struct AAC_Pixel_G AAC_Pixel<AAC_Pixel_Type::G>::GetPixelValues()
{
    return AAC_Pixel<AAC_Pixel_Type::G>::_pixel_values;
}


template<>
class AAC_Pixel<AAC_Pixel_Type::GA>
{
private:
    AAC_Pixel_GA _pixel_values;

public:
    AAC_Pixel();
    struct AAC_Pixel_GA GetPixelValues();
    void SetPixelValues();

};

AAC_Pixel<AAC_Pixel_Type::GA>::AAC_Pixel() {
    AAC_Pixel<AAC_Pixel_Type::GA>::_pixel_values.grey = 0;
    AAC_Pixel<AAC_Pixel_Type::GA>::_pixel_values.alpha = 0;
}

struct AAC_Pixel_GA AAC_Pixel<AAC_Pixel_Type::GA>::GetPixelValues()
{
    return AAC_Pixel<AAC_Pixel_Type::GA>::_pixel_values;
}



template<>
class AAC_Pixel<AAC_Pixel_Type::RGB>
{
private:
    AAC_Pixel_RGB _pixel_values;
    struct AAC_Pixel_RGB GetPixelValues();
    void SetPixelValues();

public:
    AAC_Pixel();

};

AAC_Pixel<AAC_Pixel_Type::RGB>::AAC_Pixel() {
    AAC_Pixel<AAC_Pixel_Type::RGB>::_pixel_values.red = 0;
    AAC_Pixel<AAC_Pixel_Type::RGB>::_pixel_values.green = 0;
    AAC_Pixel<AAC_Pixel_Type::RGB>::_pixel_values.blue = 0;
}

struct AAC_Pixel_RGB AAC_Pixel<AAC_Pixel_Type::RGB>::GetPixelValues()
{
    return AAC_Pixel<AAC_Pixel_Type::RGB>::_pixel_values;
}



template<>
class AAC_Pixel<AAC_Pixel_Type::RGBA>
{
private:
    AAC_Pixel_RGBA _pixel_values;

public:
    AAC_Pixel();
    struct AAC_Pixel_RGBA GetPixelValues();
    void SetPixelValues();

};

AAC_Pixel<AAC_Pixel_Type::RGBA>::AAC_Pixel() {
    AAC_Pixel<AAC_Pixel_Type::RGBA>::_pixel_values.red = 0;
    AAC_Pixel<AAC_Pixel_Type::RGBA>::_pixel_values.green = 0;
    AAC_Pixel<AAC_Pixel_Type::RGBA>::_pixel_values.blue = 0;
    AAC_Pixel<AAC_Pixel_Type::RGBA>::_pixel_values.alpha = 0;
}

struct AAC_Pixel_RGBA AAC_Pixel<AAC_Pixel_Type::RGBA>::GetPixelValues()
{
    return AAC_Pixel<AAC_Pixel_Type::RGBA>::_pixel_values;
}



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


AAC_Image::AAC_Image(string path, int size_x, int size_y, int n, unsigned char *data) : 
    _path(path), _size_x(size_x), _size_y(size_y), _n(n), pixel_type(static_cast<AAC_Pixel_Type>(n))
{
    // check arguments validity
    if(size_x > MAX_SIZE || size_y > MAX_SIZE || n < 1 || n > 4 || !data) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++) 
        {
            uint8_t val;
            snprintf((char *)&val, sizeof(uint8_t), "%hhd", *(data+y*size_x+x));
            
        }
    }
    

}

//
// Created by Pedro on 13.03.2023.
//

#include <iostream>
#include <string>
#include <system_error>
#include <thread>
#include "enums.h"
#include "structs.h"

#ifndef AAC_H
#define AAC_H

class AAC_Image;
typedef uint8_t (*AAC_BrightnessFunction)(AAC_Image);

/* -------------------------------------------------------------------------- */
/*                                 ERROR CODES                                */
/* -------------------------------------------------------------------------- */

static thread_local std::error_code AAC_error_code;


void set_AAC_error_code(std::error_code ec);
std::error_code get_AAC_error_code();
void clear_AAC_error_code();


class AAC_error_category : public std::error_category 
{
public:
    virtual const char* name() const noexcept override {
        return "AAC_error_category";
    }

    virtual std::string message(int ec) const override {
        switch (static_cast<AAC_error_codes>(ec)){
            case AAC_error_codes::INVALID_PIXEL:
                return "[AAC] Invalid pixel";
            case AAC_error_codes::INVALID_PATH:
                return "[AAC] Invalid path";
            case AAC_error_codes::INVALID_ARGUMENTS:
                return "[AAC] Invalid arguments";
            case AAC_error_codes::IMAGE_OPEN_FAIL:
                return "[AAC] Failed to open image";
            case AAC_error_codes::IMAGE_ALLOCATION_ERROR:
                return "[AAC] Failed to allocate memory for piexels array";
            case AAC_error_codes::BRIGHTNESS_CALCULATION_FAIL:
                return "[AAC] Failed to calculate image brightness array";
            default:
                return "[AAC] Unknown error";
        }
    }
};

const AAC_error_category AAC_category{};

std::error_code make_error_code(AAC_error_codes ec);

/* ------------------------------------ - ----------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                 PIXEL CLASS                                */
/* -------------------------------------------------------------------------- */

template <AAC_Pixel_Type E>
class AAC_Pixel
{
private:
    const AAC_Pixel_Type _pixel_type = E;

};

/* -------------------------------------------------------------------------- */
/*                                 IMAGE CLASS                                */
/* -------------------------------------------------------------------------- */

class AAC_Image
{
private:
    const std::string _path;
    const unsigned int _n;

    void **_pixels;

    // helper for constructor
    // convers raw data to an array of appropriet size and AAC pixel types
    

public:
    const AAC_Pixel_Type pixel_type;
    const unsigned int size_x;
    const unsigned int size_y;

    AAC_Image(std::string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data);
    ~AAC_Image();
    void *GetPixel(unsigned int x, unsigned int y);
};

/* --------------------------- GLOBAL IMAGE OPENER -------------------------- */
AAC_Image *AAC_OpenImage(std::string path);

/* -------------------------------------------------------------------------- */
/*                               CONVERTER CLASS                              */
/* -------------------------------------------------------------------------- */

class AAC_Converter
{
private:
    AAC_BrightnessFunction _brightness_function;
    const unsigned int _chunk_xsize;
    const unsigned int _chunk_ysize;

public:
    std::string convert(AAC_Image img);
};

/* -------------------------------------------------------------------------- */
/*                            BRIGHTNESS FUNCTIONS                            */
/* -------------------------------------------------------------------------- */
/* 
Template: uint8_t *brightnessfunction(AAC_Image) 

Description: brightness function must take an Image and convert it into newly allocated
2d array of uint8_t values representing brightness of pixels

Nameing: All brightness function should start with AAC_bf_ and than have a function name
example=AAC_bf_Simple

Type: Brightness function should be passed to AAC_Converter. The type needed for that is
at the beggining of the file.
*/

uint8_t *AAC_bf_SimpleAverage(AAC_Image img);

#endif //AAC_H

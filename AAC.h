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
class AAC_Chunk;
typedef uint8_t (*AAC_BrightnessFunction)(AAC_Image);
typedef char (*AAC_ChunkConvertFunction)(AAC_Chunk);

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
            case AAC_error_codes::MATRIX_ALLOCATION_ERROR:
                return "[AAC] Failed to allocate space for AAC_Matrix";
            default:
                return "[AAC] Unknown error";
        }
    }
};

const AAC_error_category AAC_category{};

std::error_code make_error_code(AAC_error_codes ec);

/* ------------------------------------ - ----------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                MATRIX CLASS                                */
/* -------------------------------------------------------------------------- */

template<typename T>
class AAC_Matrix
{
private:
    const unsigned int size_x;
    const unsigned int size_y;
    T **_matrix;

public:
    AAC_Matrix(unsigned int size_x, unsigned int size_y);
    ~AAC_Matrix();
    T GetElement(unsigned int x, unsigned int y);
    void SetElement(unsigned int x, unsigned int y, T element);
};

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
/*                                 CHUNK CLASS                                */
/* -------------------------------------------------------------------------- */

class AAC_Chunk
{
private:
    const unsigned int _X_start_index; // inclusive
    const unsigned int _X_end_index; // exclusive
    const unsigned int _Y_start_index; // inclusive
    const unsigned int _Y_end_index; // exclusive

    // pointer to external image brightness array(do not free on destroy)
    uint8_t *_data;

public:
    AAC_Chunk(unsigned int _X_start_index, unsigned int _X_end_index, unsigned int _Y_start_index, unsigned int _Y_end_index, uint8_t *data);
};

/* -------------------------------------------------------------------------- */
/*                               CONVERTER CLASS                              */
/* -------------------------------------------------------------------------- */

class AAC_Converter
{
private:

    static const float _ratio;

    AAC_BrightnessFunction _brightness_func;
    AAC_ChunkConvertFunction _chunk_convertion_func;
    AAC_Matrix<AAC_Chunk*> generateChunks(unsigned int img_x, unsigned int img_y, unsigned int chunk_size, uint8_t *data);

public:
    AAC_Converter(AAC_BrightnessFunction bf, AAC_ChunkConvertFunction cc);
    std::string createArt(AAC_Image img, AAC_Conversion_Options options);
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

/* -------------------------------------------------------------------------- */
/*                         CHUNK CONVERSION FUNCTIONS                         */
/* -------------------------------------------------------------------------- */
/*
Template: char conversionfunction(AAC_Chunk chunk)

Description: Conversion functions take a chunk and convert its set of brightness
values into a single char displayed in final image

Nameing: Should start with AAC_cc_ and then have brief function name example: AAC_cc_Simple

Type: Should be passed to AAC_Converter. Type is specified at the beggining of the file
*/

char AAC_cc_Simple(AAC_Chunk chunk);

#endif //AAC_H

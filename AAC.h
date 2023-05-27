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
template<typename T>
class AAC_Matrix;

typedef AAC_Matrix<uint8_t>* (*AAC_BrightnessFunction)(AAC_Image*);
typedef std::string (*AAC_ChunkConvertFunction)(AAC_Matrix<AAC_Chunk>*, struct AAC_Conversion_Options);

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
            case AAC_error_codes::ALOCATION_ERROR:
                return "[AAC] Alocation error";
            case AAC_error_codes::INVALID_PIXEL:
                return "[AAC] Invalid pixel type";
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
            case AAC_error_codes::MATRIX_INDEX_OUT_OF_BOUNDS:
                return "[AAC/MATRIX] Index out of range";
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
    const T GetElement(unsigned int x, unsigned int y);
    T& GetElementReference(unsigned int x, unsigned int y);
    unsigned int GetXSize();
    unsigned int GetYSize();
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

    void* _pixels_matrix;

    // helper for constructor
    // convers raw data to an array of appropriet size and AAC pixel types
    

public:
    const AAC_Pixel_Type pixel_type;
    const unsigned int size_x;
    const unsigned int size_y;

    AAC_Image(std::string path, unsigned int size_x, unsigned int size_y, unsigned int n, unsigned char *data);
    ~AAC_Image();
    void* GetMatrix();
};

/* --------------------------- GLOBAL IMAGE OPENER -------------------------- */
AAC_Image *AAC_OpenImage(std::string path);

/* -------------------------------------------------------------------------- */
/*                                 CHUNK CLASS                                */
/* -------------------------------------------------------------------------- */

class AAC_Chunk
{
private:
    unsigned int _X_start_index; // inclusive
    unsigned int _X_end_index; // exclusive
    unsigned int _Y_start_index; // inclusive
    unsigned int _Y_end_index; // exclusive

    // pointer to external image brightness array(do not free on destroy)
    AAC_Matrix<uint8_t> *_data;

public:
    AAC_Chunk();
    AAC_Chunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, AAC_Matrix<uint8_t> *data);
    void SetChunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, AAC_Matrix<uint8_t> *data);
    AAC_Matrix<uint8_t> *GetData();
    unsigned int GetXStart();
    unsigned int GetXEnd();
    unsigned int GetYStart();
    unsigned int GetYEnd();
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
    AAC_Matrix<AAC_Chunk>* generateChunks(AAC_Image* img, unsigned int chunk_size, AAC_Matrix<uint8_t>* brightness_matrix);

public:
    AAC_Converter(AAC_BrightnessFunction bf, AAC_ChunkConvertFunction cc);
    std::string CreateArt(AAC_Image* img, AAC_Conversion_Options options);
};

/* -------------------------------------------------------------------------- */
/*                            BRIGHTNESS FUNCTIONS                            */
/* -------------------------------------------------------------------------- */
/* 
Template: AAC_Matrix<uint8_t> *brightnessfunction(AAC_Image*) 

Description: brightness function must take an Image and convert it into newly allocated
AAC_Matrix<uint8_t> representing brightness of pixels

Nameing: All brightness function should start with AAC_bf_ and than have a function name
example=AAC_bf_Simple

Type: Brightness function should be passed to AAC_Converter. The type needed for that is
at the beggining of the file.
*/

AAC_Matrix<uint8_t>* AAC_bf_SimpleAverage(AAC_Image* img);

/* -------------------------------------------------------------------------- */
/*                         CHUNK CONVERSION FUNCTIONS                         */
/* -------------------------------------------------------------------------- */
/*
Template: std::string conversionfunction(AAC_Matrix<AAC_Chunk> chunks, struct AAC_Conversion_Options options)

Description:

Nameing: Should start with AAC_cc_ and then have brief function name example: AAC_cc_Simple

Type: Should be passed to AAC_Converter. Type is specified at the beggining of the file
*/

std::string AAC_cc_Simple(AAC_Matrix<AAC_Chunk>* chunks, struct AAC_Conversion_Options options);

#endif //AAC_H

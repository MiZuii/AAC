//
// Created by Pedro on 13.03.2023.
//

/**
 * @file aac.h
 *
 * @brief Main library header file
 */

#include <iostream>
#include <string>
#include <system_error>
#include <memory>
#include <thread>
#include <vector>

#define MAX_SIZE 4000

#ifndef AAC_H
#define AAC_H

/**
 * @brief AAC Matrix size type (nonnamespace)
 * 
 */
typedef unsigned long msize_t;

/**
 * @brief AAC Matrix squared size type (nonnamespace)
 * 
 */
typedef unsigned long long mmsize_t;

/**
 * @namespace AAC
 * 
 * @brief Main library namespace
 * 
 */
namespace AAC {

/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */

struct Pixel_G
{
    uint8_t grey;
};

struct Pixel_GA
{
    uint8_t grey;
    uint8_t alpha;
};

struct Pixel_RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Pixel_RGBA
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct Pixel_EMPTY {};

/* -------------------------------------------------------------------------- */
/*                                    ENUMS                                   */
/* -------------------------------------------------------------------------- */

enum class error_codes {
  ALOCATION_ERROR,
  INVALID_PIXEL,
  INVALID_PATH,
  INVALID_ARGUMENTS,
  IMAGE_OPEN_FAIL,
  IMAGE_ALLOCATION_ERROR,
  BRIGHTNESS_CALCULATION_FAIL,
  MATRIX_ALLOCATION_ERROR,
  MATRIX_INDEX_OUT_OF_BOUNDS,
  CHUNK_SIZE_ERROR,
};

enum class Pixel_Type {
  EMPTY,
  G,
  GA,
  RGB,
  RGBA,
};

/* -------------------------------------------------------------------------- */
/*                                 EXCEPTIONS                                 */
/* -------------------------------------------------------------------------- */

/**
 * @class AACException
 *
 * @brief Class providing exceptions management and messages.
 *
 */

class AACException : public std::exception {

private:
    error_codes error_code;
    const char * message(error_codes ec) const;
    
public:
    AACException(error_codes error_code) : error_code(error_code) { }
    virtual ~AACException() noexcept {}
    
    const char* what () const noexcept override {
        return message(error_code);
    }
};

/* -------------------------------------------------------------------------- */
/*                                MATRIX CLASS                                */
/* -------------------------------------------------------------------------- */

/**
 * @class Matrix
 *
 * @brief Multipurpose matrix class
 *
 */
template<typename T>
class Matrix
{
private:
    msize_t size_x;
    msize_t size_y;
    mmsize_t quantity;
    std::vector<std::vector<T>> _matrix;

public:

    Matrix(const msize_t size_x, const msize_t size_y);
    Matrix();
    Matrix(Matrix<T>& other);
    ~Matrix();
    msize_t GetXSize() const;
    msize_t GetYSize() const;
    bool isShapeOf(Matrix<T>& other) const;
    std::vector<T>& operator[](msize_t index);
    Matrix<T>& operator=(Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other);
};

#include "../sources/aac_matrix.tpp"

/* -------------------------------------------------------------------------- */
/*                                 PIXEL CLASS                                */
/* -------------------------------------------------------------------------- */

/**
 * @class Pixel
 *
 * @brief Pixel class for storing Image pixels in more organised way
 */
template <Pixel_Type E>
class Pixel
{
private:
    const Pixel_Type _pixel_type = E;
};

/* -------------------------------- GREY TYPE ------------------------------- */

template <>
class Pixel<Pixel_Type::G>
{
private:
    Pixel_G _pixel_values;

public:
    // constructors
    Pixel();
    Pixel(uint8_t grey);

    // getters and setters
    struct Pixel_G GetPixelValues();
    void SetPixelValues(uint8_t grey);
};

/* ----------------------------- GREY ALPHA TYPE ---------------------------- */

template <>
class Pixel<Pixel_Type::GA>
{
private:
    Pixel_GA _pixel_values;

public:
    // constructors
    Pixel();
    Pixel(uint8_t grey, uint8_t alpha);

    // getters and setters
    struct Pixel_GA GetPixelValues();
    void SetPixelValues(uint8_t grey, uint8_t alpha);
};

/* --------------------------- RED GREEN BLUE TYPE -------------------------- */

template <>
class Pixel<Pixel_Type::RGB>
{
private:
    Pixel_RGB _pixel_values;

public:
    // constructors
    Pixel();
    Pixel(uint8_t red, uint8_t green, uint8_t blue);

    // getters and setters
    struct Pixel_RGB GetPixelValues();
    void SetPixelValues(uint8_t red, uint8_t green, uint8_t blue);
};

/* ------------------------ RED GREEN BLUE ALPHA TYPE ----------------------- */

template <>
class Pixel<Pixel_Type::RGBA>
{
private:
    Pixel_RGBA _pixel_values;

public:
    // constructors
    Pixel();
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    // getters and setters
    struct Pixel_RGBA GetPixelValues();
    void SetPixelValues(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
};

/* ------------------------------- EMPTY TYPE ------------------------------- */

template <>
class Pixel<Pixel_Type::EMPTY>
{
private:
    Pixel_EMPTY _pixel_values;

public:
    Pixel();
};

/* -------------------------------------------------------------------------- */
/*                                 IMAGE CLASS                                */
/* -------------------------------------------------------------------------- */

/**
 * @class Image
 *
 * @brief Contains full image as pixels matrix
 *
 */
class Image
{
private:
    uint8_t _n;
    void* _pixels_matrix;
    Pixel_Type _pixel_type;
    msize_t _size_x;
    msize_t _size_y;

public:

    Image(msize_t size_x, msize_t size_y, uint8_t n, unsigned char *data);
    Image(std::string path);
    msize_t GetSizeX() const;
    msize_t GetSizeY() const;
    Pixel_Type GetPixelType() const;
    ~Image();
    void* GetMatrix();
};

/* --------------------------- GLOBAL IMAGE OPENER -------------------------- */
/**
 * @brief Global image opener
 */
Image* OpenImage(std::string path);

/* -------------------------------------------------------------------------- */
/*                                 CHUNK CLASS                                */
/* -------------------------------------------------------------------------- */

/**
 * @class Chunk
 *
 * @brief Representation of groups of pixels which are going to be replaced by single char
 *
 */
class Chunk
{
private:
    msize_t _X_start_index; // inclusive
    msize_t _X_end_index; // exclusive
    msize_t _Y_start_index; // inclusive
    msize_t _Y_end_index; // exclusive

    // pointer to external image brightness array
    std::shared_ptr<Matrix<uint8_t>> _data;

public:
    Chunk();
    Chunk(msize_t X_start_index, msize_t X_end_index, msize_t Y_start_index, msize_t Y_end_index, std::shared_ptr<Matrix<uint8_t>> data);
    void SetChunk(msize_t X_start_index, msize_t X_end_index, msize_t Y_start_index, msize_t Y_end_index, std::shared_ptr<Matrix<uint8_t>> data);
    std::shared_ptr<Matrix<uint8_t>> GetData() const;
    msize_t GetXStart() const;
    msize_t GetXEnd() const;
    msize_t GetYStart() const;
    msize_t GetYEnd() const;
};

/* -------------------------------------------------------------------------- */
/*                         RIGHTNESS CONVERTER CLASSES                        */
/* -------------------------------------------------------------------------- */

/**
 * @class BrightnessConverter
 *
 * @brief Specifies group off classes converting Image to brightness matrix
 *
 */
class BrightnessConverter
{
public:
    virtual std::shared_ptr<Matrix<uint8_t>> convert(Image* img) = 0;
};

/**
 * @class BC_Simple
 *
 * @brief Simplest possible brightness converter
 *
 */
class BC_Simple : public BrightnessConverter
{
private:
    const float _red_weight, _green_weight, _blue_weight;
    const uint8_t _negate;

public:
    BC_Simple(float red_weight, float green_weight, float blue_weight, uint8_t negate = 0);
    BC_Simple();
    std::shared_ptr<Matrix<uint8_t>> convert(Image* img) override;
};

/* -------------------------------------------------------------------------- */
/*                           CHUNK CONVERTER CLASSES                          */
/* -------------------------------------------------------------------------- */

/**
 * @class ChunkConverter
 *
 * @brief Converts chunks matrix into final string
 *
 */
class ChunkConverter
{
public:
    virtual std::string convert(Matrix<Chunk>* chunks) = 0;
};

/**
 * @class CC_Simple
 *
 * @brief Simplest possible chunk converter
 *
 */
class CC_Simple : public ChunkConverter
{
private:
    const std::string _alphabet;

public:
    CC_Simple(std::string alphabet);
    std::string convert(Matrix<Chunk>* chunks) override;

};

/**
 * @class CC_Braile
 *
 * @brief Converter that uses Braile characters (not soo ascii anymore)
 *
 */
class CC_Braile : public ChunkConverter
{
private:
    static wchar_t get_braile_char(uint8_t char_val);
    const uint8_t _bk_brightness;

public:
    CC_Braile(uint8_t break_point_brightness);
    std::string convert(Matrix<Chunk>* chunks) override;

};

/* -------------------------------------------------------------------------- */
/*                               CONVERTER CLASS                              */
/* -------------------------------------------------------------------------- */

/**
 * @class Converter
 *
 * @brief Creates main converter combining all other steps to create art
 *
 */
class Converter
{
private:

    static const float _ratio;
    BrightnessConverter* _brightness_conv;
    ChunkConverter* _chunk_conv;
    
    Matrix<Chunk>* generateChunks(Image* img, size_t chunk_size, std::shared_ptr<Matrix<uint8_t>> brightness_matrix);

public:
    Converter(BrightnessConverter* brightness_conv, ChunkConverter* chunk_conv);
    std::string CreateArt(Image* img, size_t chunk_size);
};

} // namespace AAC

#endif //AAC_H

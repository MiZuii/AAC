#ifndef STRUCTS_H
#define STRUCTS_H

struct AAC_Pixel_G
{
    uint8_t grey;
};

struct AAC_Pixel_GA
{
    uint8_t grey;
    uint8_t alpha;
};

struct AAC_Pixel_RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct AAC_Pixel_RGBA
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct AAC_Pixel_EMPTY {};

struct AAC_Conversion_Options
{
    unsigned int chunk_size;
    std::string alphabet;
};

#endif // STRUCTS_H
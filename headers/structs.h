#ifndef STRUCTS_H
#define STRUCTS_H

namespace AAC 
{

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

} // namespace AAC

#endif // STRUCTS_H
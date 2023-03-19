#ifndef STRUCTS_H
#define STRUCTS_H

struct AAC_Pixel_G
{
    int grey;
};

struct AAC_Pixel_GA
{
    int grey;
    int alpha;
};

struct AAC_Pixel_RGB
{
    int red;
    int green;
    int blue;
};

struct AAC_Pixel_RGBA
{
    int red;
    int green;
    int blue;
    int alpha;
};

struct AAC_Pixel_EMPTY {};

#endif // STRUCTS_H
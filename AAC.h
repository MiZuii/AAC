//
// Created by Pedro on 13.03.2023.
//

#include <iostream>

#ifndef AAC_H
#define AAC_H


// ENUMs
enum AAC_Pixel_Type {
    EMPTY,
    G,
    GA,
    RGB,
    RGBA,
};


// STRUCTs
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



// PIXEL CLASS DEFINITION

template <AAC_Pixel_Type E>
class AAC_Pixel
{
private:
    const AAC_Pixel_Type _pixel_type = E;

};


template<>
class AAC_Pixel<G>
{
private:
    struct AAC_Pixel_G _pixel_values;

public:
    AAC_Pixel();
    ~AAC_Pixel();

};

AAC_Pixel<G>::AAC_Pixel() {
    AAC_Pixel<G>::_pixel_values.grey = 0;
}

template<>
class AAC_Pixel<GA>
{
private:
    struct AAC_Pixel_GA _pixel_values;

public:
    AAC_Pixel();
    ~AAC_Pixel();

};

template<>
class AAC_Pixel<RGB>
{
private:
    struct AAC_Pixel_RGB _pixel_values;

public:
    AAC_Pixel();
    ~AAC_Pixel();

};

template<>
class AAC_Pixel<RGBA>
{
private:
    struct AAC_Pixel_RGBA _pixel_values;

public:
    AAC_Pixel();
    ~AAC_Pixel();

};

template<>
class AAC_Pixel<EMPTY>
{
private:
    struct AAC_Pixel_EMPTY _pixel_values;

public:
    AAC_Pixel();
    ~AAC_Pixel();

};


#endif //AAC_H

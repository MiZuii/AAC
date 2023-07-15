//
// Created by Pedro on 13.03.2023.
//

/**
 * @file aac.cpp
 * 
 * @brief Global functions and static variables for AAC.h
 */

#include <aac.h>
#include <iostream>
#include <string>

// library import for reading image format files
#define CUSTOM_FOPEN_LOAD
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
namespace AAC {

/* --------------------------- GLOBAL IMAGE OPENER -------------------------- */

/**
 * 
 * @brief Global image opener
 * 
 * @param path Path of the image to open
 * @return Image* An pointer to Image instance of the given image
 */
Image *OpenImage(std::string path) {

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

    if (!data)
    {
        throw AACException(error_codes::IMAGE_OPEN_FAIL);
    }
    else {
        Image* opened_image = new Image(x, y, n, data);
        free(data);
        return opened_image;
    }
}

/* ----------------------- FONT WIDTH TO HEIGHT RATIO ----------------------- */

/**
 * @brief Ratio of font width to height used for proper chunks division
 * 
 */
const float Converter::_ratio = 0.45;

} // namespace AAC

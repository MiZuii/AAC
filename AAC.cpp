//
// Created by Pedro on 13.03.2023.
//

#include "AAC.h"
#include <iostream>
#include <string>

// library import for reading image format files
#define CUSTOM_FOPEN_LOAD
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

/* --------------------------- GLOBAL IMAGE OPENER -------------------------- */

AAC_Image *AAC_OpenImage(std::string path) {

    int x, y, n;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

    if (!data)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PIXEL));
        throw get_AAC_error_code();
    }
    else {
        AAC_Image* opened_image = new AAC_Image(path, x, y, n, data);
        free(data);
        return opened_image;
    }
}

/* ----------------------- FONT WIDTH TO HEIGHT RATIO ----------------------- */
const float AAC_Converter::_ratio = 0.45;

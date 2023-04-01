#include <iostream>
#include <string>
#include <cstdio>

#include "AAC.h"
#include "stb_image.h"

using namespace std;

int main(int argc, char *argv[]) {

    AAC_Image *img = AAC_OpenImage("test.jpg");
    cout << static_cast<int>(img->pixel_type) << endl;
    delete img;
    return 0;
}
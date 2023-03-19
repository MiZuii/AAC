#include <iostream>
#include <string>
#include <cstdio>

#include "AAC.h"

// library import for reading image format files
#define CUSTOM_FOPEN_LOAD
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *argv[]) {

    using namespace std;
    
    int x,y,n;
    unsigned char *data = stbi_load("test.jpg", &x, &y, &n, 0);
    if(!data) {cout << stbi_failure_reason() << endl; return 1;}
    
    cout << x << "x" << y << "  " << n << endl;

    AAC_Image img = AAC_Image("test.jpg", x, y, n, data);

}
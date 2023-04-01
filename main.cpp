#include <iostream>
#include <string>
#include <cstdio>

#include "AAC.h"

// library import for reading image format files
#define CUSTOM_FOPEN_LOAD
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    int x,y,n;
    unsigned char *data = stbi_load("test.jpg", &x, &y, &n, 0);
    if(!data) {cout << stbi_failure_reason() << endl; return 1;}
    
    cout << x << "x" << y << "  " << n << endl;

    AAC_Image img = AAC_Image("test.jpg", x, y, n, data);
    uint8_t valR = data[0];
    uint8_t valG = data[1];
    uint8_t valB = data[2];
    printf("%u, %u, %u\n", valR, valG, valB);

    free(data);
    return 0;

}
#include <iostream>
#include <string>
#include <cstdio>

#include "AAC.h"
#include "stb_image.h"

using namespace std;

int main(int argc, char *argv[]) {

    AAC_Image *img = AAC_OpenImage("test.jpg");
    
    // "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // ".-=*#@"
    AAC_Conversion_Options convert_options = {3, ".-=*#@@"};
    AAC_Converter converter = AAC_Converter(AAC_bf_SimpleAverage, AAC_cc_Simple);
    
    std::string r = converter.CreateArt(img, convert_options);

    std::cout << r << std::endl;

    delete img;
    return 0;
}
#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace std;

int main(int argc, char *argv[]) {

    AAC_Image *img = AAC_OpenImage("test.png");
    
    // "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // ".-=*#@"
    
    try
    {
        AAC_BC_Simple bc;
        AAC_CC_Braile cc(128);
        AAC_Converter converter = AAC_Converter(&bc, &cc);

        string r = converter.CreateArt(img, 2);
        cout << r << endl;
    }
    catch(const std::error_code& e)
    {
        std::cerr << e.message() << '\n';
    }

    delete img;
    return 0;
}
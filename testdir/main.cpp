#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace AAC;

int main(int argc, char *argv[]) {

    Image *img = OpenImage("test.png");
    
    // "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // ".-=*#@"
    
    try
    {
        BC_Simple bc;
        CC_Braile cc(128);
        Converter converter = Converter(&bc, &cc);

        std::string r = converter.CreateArt(img, 2);
        std::cout << r << std::endl;
    }
    catch(const std::error_code& e)
    {
        std::cerr << e.message() << '\n';
    }

    delete img;
    return 0;
}
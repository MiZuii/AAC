#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace std;

int main(int argc, char *argv[]) {

    AAC_Image *img = AAC_OpenImage("test.jpg");
    
    // "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // ".-=*#@"
    AAC_BC_Simple bc;
    AAC_CC_Simple cc(".-=*#@");
    AAC_Converter converter = AAC_Converter(&bc, &cc);
    
    string r = converter.CreateArt(img, 5);

    cout << r << endl;

    delete img;
    return 0;
}
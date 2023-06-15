#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace AAC;

int main(int argc, char *argv[]) {

    /* Simple usage of the library 3 */

    /* Open image */
    Image *img = OpenImage("../example1.jpg");

    /* All of the converters has it's own specific parameters. For example
    the Simple Chunk Converter CC_Simple has it's alphabet as an argument.
    We can use that to tweak the image from example 1 soo the background on 
    the image is black. All the parameters are explained in documentation. */
    BC_Simple bc(1, 1, 1, 1);
    CC_Simple cc("   ..-==**##@@");

    /* Now go through the same steps of creating art as in the previous examples. */
    Converter converter = Converter(&bc, &cc);
    std::cout << converter.CreateArt(img, 5) << std::endl;

    delete img;
    return 0;
}
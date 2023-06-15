#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace AAC;

int main(int argc, char *argv[]) {

    /* Simple usage of the library 2 */

    /* Open image just like in example 1 */
    Image *img = OpenImage("../example2.jpg");

    /* In this example create is show that you can combine different brightness converters
    and chunk converters. All the converters need to deriviate from one base class soo for
    list of all converters see the documentation */
    BC_Simple bc(1, 1, 1, 1);
    CC_Braile cc(90);

    /* Supplying the Converter constructor with new pair of converters */
    Converter converter = Converter(&bc, &cc);

    /* Now create the art string just like in example 1. Note, some converters may need
    different chunk sizes. The Braile converter for example needs at least 2 chunks. If
    supplied with lower chunk size it will throw an error. */

    std::cout << converter.CreateArt(img, 5) << std::endl;

    delete img;
    return 0;
}
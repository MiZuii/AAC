#include <iostream>
#include <string>
#include <cstdio>
#include <aac.h>

using namespace AAC;

int main(void) {

    /* Simple usage of the library 2 */

    /* Open image just like in example 1 */
    Image *img = OpenImage("../example2.png");

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

    std::cout << converter.CreateArt(img, 13) << std::endl;

    /* There is also important thing to say about the generated image. We can see that
    the edges are a bit cut. This is because the library prioritizes cutting the edges
    to force the resolution ratio. It does this to not affect the middle part of the image. */

    delete img;
    return 0;
}
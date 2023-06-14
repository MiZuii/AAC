#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

/* Remember to use library namespace */
using namespace AAC;

int main(int argc, char *argv[]) {

    /* Simples usage of the library */

    /* Open an image from your file system with the global function OpenImage.
    This is the only function that is supposed to properly open the images in the
    AAC library althou you can work around it if you know what you're doing.*/
    Image *img = OpenImage("../example2.jpg");

    /* Create two objects. One that is a derived class from a BrightnessConverter class and
    one that is a derived class from a ChunkConverter class. This are the only two objects
    that can alter you output image ass only they are performing the image transformations. */
    BC_Simple bc(1, 1, 1, 1);
    CC_Simple cc(" .-=*#@");

    /* Supplying the Converter constructor with these two objects will create and object
    that is used to convert the img instance to a string */
    Converter converter = Converter(&bc, &cc);

    /* Use methode CreateArt of the Converter object to create ascii art representation of
    you image. You need to pass an image and chunk size(which will decide about you output
    art size, the bigger the chunk the smaller the art) */

    std::cout << converter.CreateArt(img, 5) << std::endl;

    /* You can convert you image using multiple converters. After ending work with it
    delete it ass it's dynamicly allocated. */
    delete img;

    return 0;
}
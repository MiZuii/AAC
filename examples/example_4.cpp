#include <iostream>
#include <string>
#include <cstdio>

#include "../AAC.h"

using namespace AAC;

int main(int argc, char *argv[]) {

    /* Simple usage of the library 4 */

    /* As mentioned previously the main converter takes img pointer as parameter.
    That meas that we can use the same object for multiple conversions. First make to
    Image objects(the don't need to have the same format). */
    Image *img1 = OpenImage("../example3.png");
    Image *img2 = OpenImage("../example4.png");

    /* Create the converters pair */
    BC_Simple bc(1, 1, 1, 0);
    CC_Simple cc("  ..-=**##@@");

    /* Create the converter object */
    Converter converter = Converter(&bc, &cc);

    /* Now go through the same steps of creating art as in the previous examples,
    but for two images.*/
    std::cout << "Image one:\n" << converter.CreateArt(img1, 8) << std::endl;
    std::cout << "Image two:\n" << converter.CreateArt(img2, 18) << std::endl;

    /* don't forget to delete both images */
    delete img1;
    delete img2;
    return 0;
}
#include <aac.h>

#include <locale>
#include <codecvt>
#include <string>
#include <typeinfo>

/**
 * @file aac_cc_simple.cpp
 * @brief Contains the implementation of the CC_Simple class.
 */

using namespace AAC;

/**
 * @brief Calculates the index of a character in the alphabet based on brightness.
 * 
 * @param interval_length The length of each brightness interval.
 * @param brightness The brightness value.
 * @return The index of the character in the alphabet.
 */
uint8_t get_char_index(size_t interval_length, uint8_t brightness) {
    return brightness / interval_length;
}

/**
 * @brief Construct for a Simple ASCII art converter implementation.
 */
CC_Simple::CC_Simple(std::string alphabet) : _alphabet(alphabet) {}

/**
 * @brief Converts the given matrix of chunks to a string using a simple character mapping.
 *
 * @param chunks A pointer to the matrix of chunks to be converted.
 * @return The resulting string representation of the converted chunks.
 *
 * @throws error_code An exception is thrown if the alphabet length is invalid.
 */
std::string CC_Simple::convert(Matrix<Chunk>* chunks) {

    // find the interval of the alphabet
    size_t alphabet_len = _alphabet.length();

    if (alphabet_len < 2 || alphabet_len > 255) {
        throw AACException(error_codes::INVALID_ARGUMENTS);
    }

    uint8_t interval_len = 255 / alphabet_len;


    // make resulting char matrix and gather chunk data
    Matrix<char> art_result = Matrix<char>(chunks->GetXSize(), chunks->GetYSize());
    std::shared_ptr<Matrix<uint8_t>> brightness_matrix = (*chunks)[0][0].GetData();

    // iterate through chunks and generate result
    for (msize_t y = 0; y < chunks->GetYSize(); y++) {
        for (msize_t x = 0; x < chunks->GetXSize(); x++) {

            Chunk cchunk = (*chunks)[y][x];

            unsigned long sum = 0;
            unsigned long quantity = (cchunk.GetYEnd() - cchunk.GetYStart()) * (cchunk.GetYEnd() - cchunk.GetYStart());

            for (msize_t cy = cchunk.GetYStart(); cy < cchunk.GetYEnd(); cy++) {
                for (msize_t cx = cchunk.GetXStart(); cx < cchunk.GetXEnd(); cx++) {
                    sum += (*brightness_matrix)[cy][cx];
                }
            }

            art_result[y][x] = _alphabet[get_char_index(interval_len, sum / quantity)];
        }
    }

    std::string result = "";

    // convert to final string
    for (msize_t y = 0; y < art_result.GetYSize(); y++) {
        for (msize_t x = 0; x < art_result.GetXSize(); x++) {
            result.push_back(art_result[y][x]);
        }
        result += '\n';
    }

    return result;
}

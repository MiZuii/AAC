#include "../AAC.h"

uint8_t get_char_index(size_t interval_length, uint8_t brightness) {
    return brightness / interval_length;
}

AAC_CC_Simple::AAC_CC_Simple(std::string alphabet) : _alphabet(alphabet) {}

std::string AAC_CC_Simple::convert(AAC_Matrix<AAC_Chunk>* chunks) {

    // find the interval of the alphabet
    size_t alphabet_len = _alphabet.length();

    if( alphabet_len < 2 || alphabet_len > 255 ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    uint8_t interval_len = 255 / alphabet_len;


    // make resulting char matrix and gather chunk data
    AAC_Matrix<char> art_result = AAC_Matrix<char>(chunks->GetXSize(), chunks->GetYSize());
    std::shared_ptr<AAC_Matrix<uint8_t>> brightness_matrix = chunks->GetElementReference(0, 0).GetData();

    // iterate through chunks and generate result
    for(size_t y = 0; y < chunks->GetYSize(); y++) {
        for(size_t x = 0; x < chunks->GetXSize(); x++) {

            AAC_Chunk cchunk = chunks->GetElement(x, y);

            unsigned long sum = 0;
            unsigned long quantity = (cchunk.GetYEnd() - cchunk.GetYStart())*(cchunk.GetYEnd() - cchunk.GetYStart());

            for(size_t cy = cchunk.GetYStart(); cy < cchunk.GetYEnd(); cy++) {
                for(size_t cx = cchunk.GetXStart(); cx < cchunk.GetXEnd(); cx++) {
                    sum += brightness_matrix->GetElement(cx, cy);
                }
            }

            art_result.GetElementReference(x, y) = _alphabet[get_char_index(interval_len, sum / quantity)];
        }
    }

    std::string result = "";

    // conver to final string
    for(size_t y = 0; y < art_result.GetYSize(); y++) {
        for(size_t x = 0; x < art_result.GetXSize(); x++) {

            result.push_back(art_result.GetElement(x, y));
        }
        result += '\n';
    }

    return result;
}
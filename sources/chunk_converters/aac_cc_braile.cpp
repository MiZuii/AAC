#include <aac.h>

#include <locale>
#include <codecvt>
#include <string>
#include <typeinfo>

/**
 * @file aac_cc_braile.cpp
 * @brief Contains the implementation of the CC_Braile class.
 */

using namespace AAC;

#define BRAILE_CHUNKX_DIVISOR 2
#define BRAILE_CHUNKY_DIVISOR 4

/* -------------------------------------------------------------------------- */
/*                                AAC_CC_Braile                               */
/* -------------------------------------------------------------------------- */

/**
 * @brief Converts a character value to its corresponding Braille character.
 * 
 * @param char_val The character value.
 * @return The corresponding Braille character.
 */
wchar_t CC_Braile::get_braile_char(uint8_t char_val) {
    return static_cast<wchar_t>(0x2800 + char_val);
}

/**
 * @brief Construct for a Braille ASCII art converter implementation.
 */
CC_Braile::CC_Braile(uint8_t break_point_brightness) : _bk_brightness(break_point_brightness) {}

/**
 * @brief Converts the given matrix of chunks to a string using the Braille character encoding.
 *
 * @param chunks A pointer to the matrix of chunks to be converted.
 * @return The resulting string representation of the converted chunks.
 *
 * @throws error_code An exception is thrown if the chunk size is insufficient.
 */
std::string CC_Braile::convert(Matrix<Chunk>* chunks) {

    // check if necessary chunk size is provided
    if (((*chunks)[0][0].GetXEnd() - (*chunks)[0][0].GetXStart()) < BRAILE_CHUNKX_DIVISOR ||
        ((*chunks)[0][0].GetYEnd() - (*chunks)[0][0].GetYStart()) < BRAILE_CHUNKY_DIVISOR) {
        throw AACException(error_codes::CHUNK_SIZE_ERROR);
    }

    // make resulting char matrix and gather chunk data
    Matrix<wchar_t> art_result = Matrix<wchar_t>(chunks->GetXSize(), chunks->GetYSize());
    std::shared_ptr<Matrix<uint8_t>> brightness_matrix = (*chunks)[0][0].GetData();
    Matrix<uint8_t> mini_matrix(BRAILE_CHUNKX_DIVISOR, BRAILE_CHUNKY_DIVISOR);

    // calculate columns and rows divide
    Chunk tchunk = (*chunks)[0][0];
    msize_t column_sizes[BRAILE_CHUNKX_DIVISOR + 1];
    msize_t row_sizes[BRAILE_CHUNKY_DIVISOR + 1];

    msize_t column_size = (tchunk.GetXEnd() - tchunk.GetXStart()) / BRAILE_CHUNKX_DIVISOR;
    uint8_t column_oversize = (tchunk.GetXEnd() - tchunk.GetXStart()) % BRAILE_CHUNKX_DIVISOR;

    msize_t row_size = (tchunk.GetYEnd() - tchunk.GetYStart()) / BRAILE_CHUNKY_DIVISOR;
    uint8_t row_oversize = (tchunk.GetYEnd() - tchunk.GetYStart()) % BRAILE_CHUNKY_DIVISOR;

    // apply sizes and refractor into prefix sum
    column_sizes[0] = 0;
    column_sizes[1] = column_size + (column_oversize == 1);
    column_sizes[2] = 2 * column_size + (column_oversize == 1);

    row_sizes[0] = 0;
    row_sizes[1] = row_size + (row_oversize > 2);
    row_sizes[2] = 2 * row_size + (row_oversize > 0) + (row_oversize > 2);
    row_sizes[3] = 3 * row_size + (row_oversize > 1) + (row_oversize > 0) + (row_oversize > 2);
    row_sizes[4] = 4 * row_size + (row_oversize > 1) + (row_oversize > 0) + (row_oversize > 2);

    // iterate through chunks and generate result
    for (msize_t y = 1; y < chunks->GetYSize() - 1; y++) {
        for (msize_t x = 1; x < chunks->GetXSize() - 1; x++) {

            Chunk cchunk = (*chunks)[y][x];

            // calculate chunk average brightness values for mini matrix
            for (uint8_t cell_row = 0; cell_row < BRAILE_CHUNKY_DIVISOR; cell_row++) {
                for (uint8_t cell_column = 0; cell_column < BRAILE_CHUNKX_DIVISOR; cell_column++) {

                    // iterate through given cell subcell and calculate average brightness
                    unsigned long sum = 0;
                    unsigned long quantity = (row_sizes[cell_row + 1] - row_sizes[cell_row]) * (column_sizes[cell_column + 1] - column_sizes[cell_column]);
                    size_t real_x_index, real_y_index;

                    for(real_x_index = cchunk.GetXStart() + column_sizes[cell_column]; real_x_index < cchunk.GetXStart() + column_sizes[cell_column + 1]; real_x_index++) {
                        for(real_y_index = cchunk.GetYStart() + row_sizes[cell_row]; real_y_index < cchunk.GetYStart() + row_sizes[cell_row + 1]; real_y_index++) {
                            sum += (*brightness_matrix)[real_y_index][real_x_index];
                        }
                    }

                    mini_matrix[cell_row][cell_column] = sum / quantity;
                }
            }

            art_result[y][x] = get_braile_char((mini_matrix[0][0] > _bk_brightness) + 
                                                2*(mini_matrix[1][0] > _bk_brightness) + 
                                                4*(mini_matrix[2][0] > _bk_brightness) + 
                                                8*(mini_matrix[0][1] > _bk_brightness) + 
                                                16*(mini_matrix[1][1] > _bk_brightness) + 
                                                32*(mini_matrix[2][1] > _bk_brightness) + 
                                                64*(mini_matrix[3][0] > _bk_brightness) +
                                                128*(mini_matrix[3][1] > _bk_brightness));
        }
    }

    std::wstring result = L"";

    // conver to final string
    for(msize_t y = 0; y < art_result.GetYSize(); y++) {
        for(msize_t x = 0; x < art_result.GetXSize(); x++) {

            result.push_back(art_result[y][x]);
        }
        result += '\n';
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string converted_result = converter.to_bytes(result);
    return converted_result;
}


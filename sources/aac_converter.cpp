#include <aac.h>

/**
 * @file aac_converter.cpp
 * @brief Contains the implementation of the Converter class.
 */

using namespace AAC;

/**
 * @brief Constructs a Converter object with the specified brightness converter and chunk converter.
 *
 * @param brightness_conv The brightness converter.
 * @param chunk_conv The chunk converter.
 */
Converter::Converter(BrightnessConverter* brightness_conv, ChunkConverter* chunk_conv) :
    _brightness_conv(brightness_conv), _chunk_conv(chunk_conv) {}

/**
 * @brief Generates chunks from the image using the specified chunk size and brightness matrix.
 *
 * @param img The image to generate chunks from.
 * @param chunk_size The size of each chunk.
 * @param brightness_matrix The shared pointer to the brightness matrix.
 * @return The matrix of generated chunks.
 * @throw std::error_code if the brightness matrix or image is null.
 */
Matrix<Chunk>* Converter::generateChunks(Image *img, size_t chunk_size, std::shared_ptr<Matrix<uint8_t>> brightness_matrix) {

    if (NULL == brightness_matrix) {
        throw AACException(error_codes::INVALID_ARGUMENTS);
    }

    size_t x_nof_chunks = img->GetSizeX() / chunk_size;
    size_t lcols_to_cut = (img->GetSizeX() % chunk_size) / 2;

    size_t y_chunk_size = (size_t)((float)chunk_size / _ratio);
    size_t y_nof_chunks = img->GetSizeY() / y_chunk_size;
    size_t urows_to_cut = (img->GetSizeY() % y_chunk_size) / 2;

    Matrix<Chunk>* arr = new Matrix<Chunk>(x_nof_chunks, y_nof_chunks);

    for (size_t i = 0; i < y_nof_chunks; i++) {
        for (size_t j = 0; j < x_nof_chunks; j++) {
            (*arr)[i][j].SetChunk(lcols_to_cut + j * chunk_size,
                                  lcols_to_cut + (j + 1) * chunk_size,
                                  urows_to_cut + i * y_chunk_size,
                                  urows_to_cut + (i + 1) * y_chunk_size,
                                  brightness_matrix);
        }
    }

    return arr;
}

/**
 * @brief Creates ASCII art from the image using the specified chunk size.
 *
 * @param img The image to create ASCII art from.
 * @param chunk_size The size of each chunk.
 * @return The generated ASCII art.
 * @throw std::error_code if the image is null.
 */
std::string Converter::CreateArt(Image* img, size_t chunk_size) {

    if (NULL == img) {
        throw AACException(error_codes::INVALID_ARGUMENTS);
    }

    std::shared_ptr<Matrix<uint8_t>> brightness_m = _brightness_conv->convert(img);
    Matrix<Chunk>* chunked_image = generateChunks(img, chunk_size, brightness_m);
    std::string art = _chunk_conv->convert(chunked_image);
    delete chunked_image;
    return art;
}

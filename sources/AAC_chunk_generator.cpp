#include "../AAC.h"

AAC_Converter::AAC_Converter(AAC_BrightnessConverter* brightness_conv, AAC_ChunkConverter* chunk_conv) : _brightness_conv(brightness_conv), _chunk_conv(chunk_conv) {}

AAC_Matrix<AAC_Chunk>* AAC_Converter::generateChunks(AAC_Image *img, size_t chunk_size, std::shared_ptr<AAC_Matrix<uint8_t>> brightness_matrix) {

    if( NULL == brightness_matrix || NULL == img ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    size_t x_nof_chunks = img->size_x / chunk_size;
    size_t lcols_to_cut = (img->size_x - chunk_size * x_nof_chunks) / 2;

    size_t y_chunk_size = (size_t)((float)chunk_size / _ratio);
    size_t y_nof_chunks = img->size_y / y_chunk_size;
    size_t urows_to_cut = (img->size_y - y_chunk_size * y_nof_chunks) / 2;

    AAC_Matrix<AAC_Chunk>* arr = new AAC_Matrix<AAC_Chunk>(x_nof_chunks, y_nof_chunks);

    for (size_t i = 0; i < y_nof_chunks; i++)
    {
        for (size_t j = 0; j < x_nof_chunks; j++)
        {
            arr->GetElementReference(j, i).SetChunk(lcols_to_cut + j * chunk_size,
                                                   lcols_to_cut + (j + 1) * chunk_size,
                                                   urows_to_cut + i * y_chunk_size,
                                                   urows_to_cut + (i + 1) * y_chunk_size,
                                                   brightness_matrix);
        }
    }

    return arr;
}

std::string AAC_Converter::CreateArt(AAC_Image* img, size_t chunk_size) {

    if( NULL == img ) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_ARGUMENTS));
        throw get_AAC_error_code();
    }

    std::shared_ptr<AAC_Matrix<uint8_t>> brightness_m = _brightness_conv->convert(img);
    AAC_Matrix<AAC_Chunk>* chunked_image = generateChunks(img, chunk_size, brightness_m);
    std::string art = _chunk_conv->convert(chunked_image);
    delete chunked_image;
    return art;
}
#include "../AAC.h"

AAC_Chunk::AAC_Chunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, std::shared_ptr<AAC_Matrix<uint8_t>> data) : _X_start_index(X_start_index), _X_end_index(X_end_index), _Y_start_index(Y_start_index), _Y_end_index(Y_end_index), _data(data) {}

AAC_Chunk::AAC_Chunk() : AAC_Chunk(0, 0, 0, 0, NULL) {}

void AAC_Chunk::SetChunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, std::shared_ptr<AAC_Matrix<uint8_t>> data)
{
    _X_start_index = X_start_index;
    _X_end_index = X_end_index;
    _Y_start_index = Y_start_index;
    _Y_end_index = Y_end_index;
    _data = data;
}

std::shared_ptr<AAC_Matrix<uint8_t>> AAC_Chunk::GetData() {
    return _data;
}

unsigned int AAC_Chunk::GetXStart() {
    return _X_start_index;
}

unsigned int AAC_Chunk::GetYStart() {
    return _Y_start_index;
}

unsigned int AAC_Chunk::GetXEnd() {
    return _X_end_index;
}

unsigned int AAC_Chunk::GetYEnd() {
    return _Y_end_index;
}
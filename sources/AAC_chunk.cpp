#include "../AAC.h"

AAC::Chunk::Chunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, std::shared_ptr<AAC::Matrix<uint8_t>> data) : _X_start_index(X_start_index), _X_end_index(X_end_index), _Y_start_index(Y_start_index), _Y_end_index(Y_end_index), _data(data) {}

AAC::Chunk::Chunk() : AAC::Chunk(0, 0, 0, 0, NULL) {}

void AAC::Chunk::SetChunk(unsigned int X_start_index, unsigned int X_end_index, unsigned int Y_start_index, unsigned int Y_end_index, std::shared_ptr<AAC::Matrix<uint8_t>> data)
{
    _X_start_index = X_start_index;
    _X_end_index = X_end_index;
    _Y_start_index = Y_start_index;
    _Y_end_index = Y_end_index;
    _data = data;
}

std::shared_ptr<AAC::Matrix<uint8_t>> AAC::Chunk::GetData() const {
    return _data;
}

unsigned int AAC::Chunk::GetXStart() const {
    return _X_start_index;
}

unsigned int AAC::Chunk::GetYStart() const {
    return _Y_start_index;
}

unsigned int AAC::Chunk::GetXEnd() const {
    return _X_end_index;
}

unsigned int AAC::Chunk::GetYEnd() const {
    return _Y_end_index;
}
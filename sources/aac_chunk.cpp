#include <aac.h>

/**
 * @file aac_chunk.cpp
 * @brief Contains the implementation of the Chunk class.
 */

using namespace AAC;

/**
 * @brief Constructs a Chunk object with the specified parameters.
 *
 * @param X_start_index The starting index of the X-axis.
 * @param X_end_index The ending index of the X-axis.
 * @param Y_start_index The starting index of the Y-axis.
 * @param Y_end_index The ending index of the Y-axis.
 * @param data The shared pointer to the data matrix.
 */
Chunk::Chunk(msize_t X_start_index, msize_t X_end_index, msize_t Y_start_index, msize_t Y_end_index, std::shared_ptr<Matrix<uint8_t>> data) :
    _X_start_index(X_start_index), _X_end_index(X_end_index), _Y_start_index(Y_start_index), _Y_end_index(Y_end_index), _data(data) {}

/**
 * @brief Constructs a Chunk object with default values.
 */
Chunk::Chunk() : Chunk(0, 0, 0, 0, NULL) {}

/**
 * @brief Sets the parameters of the Chunk object.
 *
 * @param X_start_index The starting index of the X-axis.
 * @param X_end_index The ending index of the X-axis.
 * @param Y_start_index The starting index of the Y-axis.
 * @param Y_end_index The ending index of the Y-axis.
 * @param data The shared pointer to the data matrix.
 */
void Chunk::SetChunk(msize_t X_start_index, msize_t X_end_index, msize_t Y_start_index, msize_t Y_end_index, std::shared_ptr<Matrix<uint8_t>> data) {
    _X_start_index = X_start_index;
    _X_end_index = X_end_index;
    _Y_start_index = Y_start_index;
    _Y_end_index = Y_end_index;
    _data = data;
}

/**
 * @brief Gets the shared pointer to the data matrix of the Chunk.
 *
 * @return The shared pointer to the data matrix.
 */
std::shared_ptr<Matrix<uint8_t>> Chunk::GetData() const {
    return _data;
}

/**
 * @brief Gets the starting index of the X-axis for the Chunk.
 *
 * @return The starting index of the X-axis.
 */
msize_t Chunk::GetXStart() const {
    return _X_start_index;
}

/**
 * @brief Gets the starting index of the Y-axis for the Chunk.
 *
 * @return The starting index of the Y-axis.
 */
msize_t Chunk::GetYStart() const {
    return _Y_start_index;
}

/**
 * @brief Gets the ending index of the X-axis for the Chunk.
 *
 * @return The ending index of the X-axis.
 */
msize_t Chunk::GetXEnd() const {
    return _X_end_index;
}

/**
 * @brief Gets the ending index of the Y-axis for the Chunk.
 *
 * @return The ending index of the Y-axis.
 */
msize_t Chunk::GetYEnd() const {
    return _Y_end_index;
}

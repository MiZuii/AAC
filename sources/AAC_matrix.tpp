/**
 * @file AAC_matrix.tpp
 * @brief Contains the implementation of the AAC::Matrix class.
 */

template <typename T>
/**
 * @brief Constructs a Matrix object with the specified size.
 * @param size_x The size in the x-axis.
 * @param size_y The size in the y-axis.
 */
AAC::Matrix<T>::Matrix(const unsigned int size_x, const unsigned int size_y) : size_x(size_x), size_y(size_y)
{
    _matrix = std::vector<std::vector<T>>(size_y);

    for( unsigned int row; row < size_y; row++ ) {
        _matrix[row] = std::vector<T>(size_x);
    }
}

template <typename T>
/**
 * @brief Destructor for the Matrix object.
 */
AAC::Matrix<T>::~Matrix()
{
    // empty for now -> to be deleted
}

template <typename T>
/**
 * @brief Retrieves the size in the x-axis of the matrix.
 * @return The size in the x-axis.
 */
unsigned int AAC::Matrix<T>::GetXSize() const {
    return size_x;
}

template <typename T>
/**
 * @brief Retrieves the size in the y-axis of the matrix.
 * @return The size in the y-axis.
 */
unsigned int AAC::Matrix<T>::GetYSize() const {
    return size_y;
}

template <typename T>
/**
 * @brief Retrieves the array element as reference.
 * @return The array element reference.
 */
std::vector<T>& AAC::Matrix<T>::operator[](unsigned int index) {
    try
    {
        return _matrix[index];
    }
    catch(const std::out_of_range& exp)
    {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw AAC::get_error_code();
    }
}

template <typename T>
/**
 * @brief Tells if the arrays are the same shape.
 * @return True if same shapes.
 */
bool AAC::Matrix<T>::isShapeOf(Matrix<T>& other) const {
    return( this->GetXSize() == other->GetXSize() && this->GetYSize() == other->GetYSize() );
}

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
AAC::Matrix<T>::Matrix(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y)
{
    _matrix = new T *[size_y];
    if (NULL == _matrix)
    {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_ALLOCATION_ERROR));
        throw AAC::get_error_code();
    }

    for (unsigned int i = 0; i < size_y; i++)
    {
        _matrix[i] = new T[size_x];

        if (NULL == _matrix[i])
        {
            AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_ALLOCATION_ERROR));
            throw AAC::get_error_code();
        }
    }
}

template <typename T>
/**
 * @brief Destructor for the Matrix object.
 */
AAC::Matrix<T>::~Matrix()
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

template <typename T>
/**
 * @brief Retrieves the element at the specified position.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return The element at the specified position.
 */
T AAC::Matrix<T>::GetElement(unsigned int x, unsigned int y) const
{
    if (x >= size_x || y >= size_y)
    {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw AAC::get_error_code();
    }
    return _matrix[y][x];
}

template <typename T>
/**
 * @brief Retrieves a reference to the element at the specified position.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return A reference to the element at the specified position.
 */
T &AAC::Matrix<T>::GetElementReference(unsigned int x, unsigned int y)
{
    if (x >= size_x || y >= size_y)
    {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw AAC::get_error_code();
    }
    return _matrix[y][x];
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

/**
 * @file AAC_matrix.tpp
 * @brief Contains the implementation of the AAC::Matrix class.
 */

template <typename T>
/**
 * @brief Constructs a Matrix object with size (0, 0).
 */
AAC::Matrix<T>::Matrix() : size_x(0), size_y(0), quantity(0) { }

template <typename T>
/**
 * @brief Constructs a Matrix object with the specified size.
 * @param size_x The size in the x-axis.
 * @param size_y The size in the y-axis.
 */
AAC::Matrix<T>::Matrix(const msize_t size_x, const msize_t size_y) : size_x(size_x), size_y(size_y), quantity(size_x*size_y)
{
    _matrix = std::vector<std::vector<T>>(size_y);

    for( msize_t row = 0; row < size_y; row++ ) {
        _matrix[row] = std::vector<T>(size_x);
    }
}

template <typename T>
/**
 * @brief Copy constructor of Matrix.
 * @param other The matrix to construct from.
 */
AAC::Matrix<T>::Matrix(AAC::Matrix<T>& other) : size_x(other.size_x), size_y(other.size_y), quantity(other.quantity)
{
    _matrix = other._matrix;
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
msize_t AAC::Matrix<T>::GetXSize() const {
    return size_x;
}

template <typename T>
/**
 * @brief Retrieves the size in the y-axis of the matrix.
 * @return The size in the y-axis.
 */
msize_t AAC::Matrix<T>::GetYSize() const {
    return size_y;
}

template <typename T>
/**
 * @brief Retrieves the array element as reference.
 * @return The array element reference.
 */
std::vector<T>& AAC::Matrix<T>::operator[](msize_t index) {
    if( 0 == quantity ) {
        AAC::set_error_code(AAC::make_error_code(AAC::error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw AAC::get_error_code();
    }
    return _matrix[index];
}

template <typename T>
/**
 * @brief Tells if the arrays are the same shape.
 * @return True if same shapes.
 */
bool AAC::Matrix<T>::isShapeOf(Matrix<T>& other) const {
    return( this->GetXSize() == other->GetXSize() && this->GetYSize() == other->GetYSize() );
}

template <typename T>
/**
 * @brief Assignment operator for Matrix.
 */
AAC::Matrix<T>& AAC::Matrix<T>::operator=(AAC::Matrix<T>& other) {
    other.size_x = this->size_x;
    other.size_y = this->size_y;
    other._matrix = this->_matrix;
    other.quantity = this->quantity;
    return *this;
}

template <typename T>
/**
 * @brief Move operator for Matrix.
 */
AAC::Matrix<T>& AAC::Matrix<T>::operator=(AAC::Matrix<T>&& other) {
    other.size_x = this->size_x;
    other.size_y = this->size_y;
    other.quantity = this->quantity;
    other._matrix = std::move(this->_matrix);
    return *this;
}

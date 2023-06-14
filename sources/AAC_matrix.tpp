template <typename T>
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
AAC::Matrix<T>::~Matrix()
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

template <typename T>
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
unsigned int AAC::Matrix<T>::GetXSize() const {
    return size_x;
}

template <typename T>
unsigned int AAC::Matrix<T>::GetYSize() const {
    return size_y;
}
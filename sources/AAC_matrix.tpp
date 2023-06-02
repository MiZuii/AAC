template <typename T>
AAC_Matrix<T>::AAC_Matrix(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y)
{
    _matrix = new T *[size_y];
    if (NULL == _matrix)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
        throw get_AAC_error_code();
    }

    for (unsigned int i = 0; i < size_y; i++)
    {
        _matrix[i] = new T[size_x];

        if (NULL == _matrix[i])
        {
            set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_ALLOCATION_ERROR));
            throw get_AAC_error_code();
        }
    }
}

template <typename T>
AAC_Matrix<T>::~AAC_Matrix()
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

template <typename T>
const T AAC_Matrix<T>::GetElement(unsigned int x, unsigned int y)
{
    if (x >= size_x || y >= size_y)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw get_AAC_error_code();
    }
    return _matrix[y][x];
}

template <typename T>
T &AAC_Matrix<T>::GetElementReference(unsigned int x, unsigned int y)
{
    if (x >= size_x || y >= size_y)
    {
        set_AAC_error_code(make_error_code(AAC_error_codes::MATRIX_INDEX_OUT_OF_BOUNDS));
        throw get_AAC_error_code();
    }
    return _matrix[y][x];
}

template <typename T>
unsigned int AAC_Matrix<T>::GetXSize() {
    return size_x;
}

template <typename T>
unsigned int AAC_Matrix<T>::GetYSize() {
    return size_y;
}
#include "../AAC.h"

void set_AAC_error_code(std::error_code ec)
{
    AAC_error_code = ec;
}

std::error_code get_AAC_error_code()
{
    return AAC_error_code;
}

void clear_AAC_error_code()
{
    AAC_error_code = std::error_code{};
}

std::error_code make_error_code(AAC_error_codes ec)
{
    return std::error_code{static_cast<int>(ec), AAC_category};
}
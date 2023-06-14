#include "../AAC.h"

void AAC::set_error_code(std::error_code ec)
{
    AAC::error_code = ec;
}

std::error_code AAC::get_error_code()
{
    return AAC::error_code;
}

void AAC::clear_error_code()
{
    AAC::error_code = std::error_code{};
}

std::error_code AAC::make_error_code(AAC::error_codes ec)
{
    return std::error_code{static_cast<int>(ec), AAC::category};
}
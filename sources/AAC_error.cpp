#include "../AAC.h"

/**
 * @brief Sets the error code for AAC.
 * @param ec The error code to set.
 */
void AAC::set_error_code(std::error_code ec)
{
    AAC::error_code = ec;
}

/**
 * @brief Gets the current error code for AAC.
 * @return The current error code.
 */
std::error_code AAC::get_error_code()
{
    return AAC::error_code;
}

/**
 * @brief Clears the error code for AAC.
 */
void AAC::clear_error_code()
{
    AAC::error_code = std::error_code{};
}

/**
 * @brief Creates an error code from the given error code value.
 * @param ec The error code value.
 * @return The error code.
 */
std::error_code AAC::make_error_code(AAC::error_codes ec)
{
    return std::error_code{static_cast<int>(ec), AAC::category};
}

#include <aac.h>

/**
 * @file aac_exception.cpp
 * @brief Contains the implementation of exception system functions for the library
 */

using namespace AAC;

/**
 * @brief Return message for given error code.
 * 
 * @param ec The error code to get message for.
 * @return std::string The error message.
 */
const char * AACException::message(error_codes ec) const {
    switch (ec){
        case error_codes::ALOCATION_ERROR:
            return "[AAC] Alocation error";
        case error_codes::INVALID_PIXEL:
            return "[AAC] Invalid pixel type";
        case error_codes::INVALID_PATH:
            return "[AAC] Invalid path";
        case error_codes::INVALID_ARGUMENTS:
            return "[AAC] Invalid arguments";
        case error_codes::IMAGE_OPEN_FAIL:
            return "[AAC] Failed to open image";
        case error_codes::IMAGE_ALLOCATION_ERROR:
            return "[AAC] Failed to allocate memory for piexels array";
        case error_codes::BRIGHTNESS_CALCULATION_FAIL:
            return "[AAC] Failed to calculate image brightness array";
        case error_codes::MATRIX_ALLOCATION_ERROR:
            return "[AAC] Failed to allocate space for Matrix";
        case error_codes::MATRIX_INDEX_OUT_OF_BOUNDS:
            return "[AAC] Index out of range";
        case error_codes::CHUNK_SIZE_ERROR:
            return "[AAC] To small chunks for conversion";
        default:
            return "[AAC] Unknown error";
    }
}

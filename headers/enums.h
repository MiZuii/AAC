#ifndef ENUMS_H
#define ENUMS_H

enum class AAC_error_codes {
  INVALID_PIXEL,
  INVALID_PATH,
  INVALID_ARGUMENTS,
  IMAGE_OPEN_FAIL,
  IMAGE_ALLOCATION_ERROR,
  BRIGHTNESS_CALCULATION_FAIL,
  MATRIX_ALLOCATION_ERROR,
};

enum class AAC_Pixel_Type {
    EMPTY,
    G,
    GA,
    RGB,
    RGBA,
};

#endif // ENUMS_H
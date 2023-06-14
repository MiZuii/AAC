#ifndef ENUMS_H
#define ENUMS_H

namespace AAC {

enum class error_codes {
  ALOCATION_ERROR,
  INVALID_PIXEL,
  INVALID_PATH,
  INVALID_ARGUMENTS,
  IMAGE_OPEN_FAIL,
  IMAGE_ALLOCATION_ERROR,
  BRIGHTNESS_CALCULATION_FAIL,
  MATRIX_ALLOCATION_ERROR,
  MATRIX_INDEX_OUT_OF_BOUNDS,
  CHUNK_SIZE_ERROR,
};

enum class Pixel_Type {
  EMPTY,
  G,
  GA,
  RGB,
  RGBA,
};

} // namespace AAC

#endif // ENUMS_H
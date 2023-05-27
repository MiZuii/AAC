#ifndef ENUMS_H
#define ENUMS_H

enum class AAC_error_codes {
  ALOCATION_ERROR,
  INVALID_PIXEL,
  INVALID_PATH,
  INVALID_ARGUMENTS,
  IMAGE_OPEN_FAIL,
  IMAGE_ALLOCATION_ERROR,
  BRIGHTNESS_CALCULATION_FAIL,
  MATRIX_ALLOCATION_ERROR,
  MATRIX_INDEX_OUT_OF_BOUNDS,
};

enum class AAC_Pixel_Type {
  EMPTY,
  G,
  GA,
  RGB,
  RGBA,
};

enum class AAC_BrightnessConverter_Type {
  SIGNLE_PIXEL,
  NINE_PIXEL,
  GRADIENT_PIXEL,      
}

enum class AAC_ChunkConverter_Type {
  SINGLE_CHUNK,
  NINE_CHUNK,
  GRADIENT_CHUNK,
}

#endif // ENUMS_H
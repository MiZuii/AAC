#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#ifndef TTF_READER
#define TTF_READER

#define SUCCESS 0
#define FAILURE -1
#define FILE_OPEN_FAIL -2
#define READ_FAIL -3
#define SEEK_FAIL -4
#define ALLOC_FAIL -5
#define NO_SUPPORTED_PLATFORM -6
#define NO_SUPPORTED_CMAP_FORMAT -7
#define NO_SUPPORTED_SCALAR_TYPE -8
#define MISSING_MANDATORY_TABLE -9

#define MISSING_GLYPH 0

// cmap formats
#define CMAP_FORMAT_0 0
#define CMAP_FORMAT_4 4
#define CMAP_FORMAT_6 6
#define CMAP_FORMAT_12 12
#define SUPPORTED_FORMAT(x) (x == CMAP_FORMAT_0 | x == CMAP_FORMAT_4 | x == CMAP_FORMAT_6 | x == CMAP_FORMAT_12 | x == GLYF_TAG)


// Tables manual: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6.html
#include "ttf_tables_defs.tpp"

// endian converters
#define _ENDIAN_SWITCH_64(x) (x << 56) | (x >> 56) |        \
    ((x >> 40) & 0xFF00) | ((x << 40) & 0xFF000000000000) | \
    ((x >> 24) & 0xFF0000) | ((x << 24) & 0xFF0000000000) | \
    ((x >> 8) & 0xFF000000) | ((x << 8) & 0xFF00000000)
#define _ENDIAN_SWITCH_32(x) (x << 24) | (x >> 24) |        \
    ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000)
#define _ENDIAN_SWITCH_16(x) (x << 8) | (x >> 8)

#define ENDIAN_SWITCH_64_L(x) x = _ENDIAN_SWITCH_64(x)
#define ENDIAN_SWITCH_32_L(x) x = _ENDIAN_SWITCH_32(x)
#define ENDIAN_SWITCH_16_L(x) x = _ENDIAN_SWITCH_16(x)

#define ENDIAN_SWITCH_64(dest, src) dest = _ENDIAN_SWITCH_64(src)
#define ENDIAN_SWITCH_32(dest, src) dest = _ENDIAN_SWITCH_32(src)
#define ENDIAN_SWITCH_16(dest, src) dest = _ENDIAN_SWITCH_16(src)

/**
 * @brief Structure containing read contest of the .ttf file
 * @details The structure is created after reading straight from the .ttf file. It contains
 *  few of the filled tables, but only the ones that can be read straight from file without 
 *  additional interpreting. The rest of the data is allocated to dynamic buffors and waits 
 *  to be parsed into proper structures.
 *  The 'loca' table is an exception because it's very easy to allocate it simultiniusly with
 *  reading the .ttf file.
 * 
 */
typedef struct _ttf_data {
    TT_HEAD_TABLE head_table;
    TT_MAXP_TABLE maxp_table;
    TT_LOCA_TABLE loca_table;
    uint8_t cmap_format; // trimmed format (technicly format should range from 0 to 14)
    void* cmap_table_format;
    void* glyf_table_raw;
}ttf_data;


int create_ttf_data(ttf_data *data, const char *ttf_file_path);
int alphabet_inclusion_check(ttf_data *data, const char *alphabet);
int16_t get_index_f0(ttf_data *data, char chr);
int32_t get_index_f4(ttf_data *data, char chr);
int get_index_f6(ttf_data *data, char chr);
int get_index_f12(ttf_data *data, char chr);

#endif // TTF_READER
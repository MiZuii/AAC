#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#ifndef TTF_READER
#define TTF_READER

#define LINEAR_SEARCH_LIMIT 22 
    /* if number of tabels is larger than 22 the linear search becomes slower than the binary search. 
    APPLIES ONLY WHEN SEARCHING FOR 5 DIRECTORY TABLES. To calculate the limit formula 5*log2(x)<x was calculated */

#define SUCCESS 0
#define FAILURE -1
#define FILE_OPEN_FAIL -2
#define READ_FAIL -3
#define SEEK_FAIL -4
#define ALLOC_FAIL -5
#define NO_SUPPORTED_PLATFORM -6
#define NO_SUPPORTED_CMAP_FORMAT -7

// ttf tables tags
#define HEAD_TAG 0x68656164
#define MAXP_TAG 0x6d617870
#define LOCA_TAG 0x6c6f6361
#define CMAP_TAG 0x636d6170
#define GLYF_TAG 0x676c7966
#define SEARCHED_TAG(x) (x == HEAD_TAG | x == MAXP_TAG | x == LOCA_TAG | x == CMAP_TAG | x == GLYF_TAG)

#define CLOSE_RETURN(fd) close(fd); return

// cmap formats
#define CMAP_FORMAT_0 0
#define CMAP_FORMAT_4 4
#define CMAP_FORMAT_6 6
#define CMAP_FORMAT_12 12

// Tables manual: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6.html
#include "ttf_tables_defs.tpp"


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
    char* cmap_table_format_raw;
    char* glyf_table_raw;
}ttf_data;


int create_ttf_data(ttf_data *data, const char *ttf_file_path);

#endif // TTF_READER
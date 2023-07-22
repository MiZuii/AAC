#include <ttf_reader.h>
#include <unistd.h>

#pragma once

// offset table scalar types to check if font is a true type font
#define TRUE_SCALAR_0 0x74727565
#define TRUE_SCALAR_1 0x00010000

#define NUM_MANDATORY_TABLES 5

#define LINEAR_SEARCH_LIMIT 22 
    /* if number of tabels is larger than 22 the linear search becomes slower than the binary search. 
    APPLIES ONLY WHEN SEARCHING FOR 5 DIRECTORY TABLES. To calculate the limit formula 5*log2(x)<x was calculated */

// ttf tables tags
#define HEAD_TAG 0x68656164
#define MAXP_TAG 0x6d617870
#define LOCA_TAG 0x6c6f6361
#define CMAP_TAG 0x636d6170
#define GLYF_TAG 0x676c7966
#define SEARCHED_TAG(x) (x == HEAD_TAG | x == MAXP_TAG | x == LOCA_TAG | x == CMAP_TAG | x == GLYF_TAG)

#define CLOSE_RETURN(fd) close(fd); return

int read_n_stayback(int fd, off_t offset, void *buf, size_t nbytes);
int read_at_offset(int fd, off_t offset, void *buf, size_t nbytes);

int read_offset_table(int fd, TT_OFFSET_TABLE *offset_table);
int read_directory_table(int fd, TT_DIRECTORY_TABLE *directory_table);
int read_head_table(int fd, off_t offset, TT_HEAD_TABLE *head_table);
int read_maxp_table(int fd, off_t offset, TT_MAXP_TABLE *maxp_table);
int read_loca_table(int fd, off_t offset, TT_LOCA_TABLE *loca_table, int16_t indexToLocFormat, uint16_t numGlyphs);
int read_cmap_table(int fd, off_t offset, ttf_data *data);

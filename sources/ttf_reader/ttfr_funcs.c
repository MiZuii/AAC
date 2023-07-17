#include <ttf_reader.h>
#include "ttfr_funcs.h"

#include <memory.h>
#include <stdint.h>

#define SEGCOUNT_OFFSET 48
#define ENTRYCOUNT_OFFSET 64
#define LENGTH_OFFSET 32

/**
 * @brief Function read() but reads from the offset and goes back to the previous fd state.
 * 
 * @param fd File descyptor to read from.
 * @param offset The offset relative to the begining of the file.
 * @param buf The buffer to save data to.
 * @param nbytes Number of bytes to read.
 * @return Same as read() except lseek failure than -1.
 */
int read_ngoback(int fd, off_t offset, void *buf, size_t nbytes) {
    off_t file_pos_buf = lseek(fd, 0, SEEK_CUR);
    size_t rbytes;
    if( file_pos_buf < 0 ) {
        return FAILURE;
    }

    if( lseek(fd, offset, SEEK_SET) < 0 ) {
        return FAILURE;
    }

    if( (rbytes = read(fd, buf, nbytes)) < 0 ) {
        return FAILURE;
    }

    if( lseek(fd, file_pos_buf, SEEK_SET) < 0 ) {
        return FAILURE;
    }
    
    return rbytes;
}

/**
 * @brief Allocate and save in buf the cmap format 0 table.
 * 
 * @param fd File to get the table from.
 * @param offset Offset in file locating the table.
 * @param buf The buffer to allocate the data to.
 * @return 0 on succes. Negative integer on Fail.
 */
int get_format0_table(int fd, off_t offset, char *buf) {

    buf = malloc(TT_CMAP_FORMAT_0_SUBTABLE_SIZE);
    if( NULL == buf ) {
        return FAILURE;
    }

    if( read_ngoback(fd, offset, buf, TT_CMAP_FORMAT_0_SUBTABLE_SIZE) < 0 ) {
        free(buf);
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Allocate and save in buf the cmap format 4 table.
 * 
 * @param fd File to get the table from.
 * @param offset Offset in file locating the table.
 * @param buf The buffer to allocate the data to.
 * @return 0 on succes. Negative integer on Fail.
 */
int get_format4_table(int fd, off_t offset, char *buf) {

    uint16_t segCountX2;
    if( read_ngoback(fd, offset + SEGCOUNT_OFFSET, &segCountX2, sizeof(uint16_t)) < 0 ) {
        return FAILURE;
    }

    buf = malloc(TT_CMAP_FORMAT_4_SUBTABLE_SIZE(segCountX2 >> 1));
    if( NULL == buf ) {
        return FAILURE;
    }

    if( read_ngoback(fd, offset, buf, TT_CMAP_FORMAT_4_SUBTABLE_SIZE(segCountX2 >> 1)) < 0 ) {
        free(buf);
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Allocate and save in buf the cmap format 6 table.
 * 
 * @param fd File to get the table from.
 * @param offset Offset in file locating the table.
 * @param buf The buffer to allocate the data to.
 * @return 0 on succes. Negative integer on Fail.
 */
int get_format6_table(int fd, off_t offset, char *buf) {

    uint16_t entryCount;
    if( read_ngoback(fd, offset + ENTRYCOUNT_OFFSET, &entryCount, sizeof(uint16_t)) < 0 ) {
        return FAILURE;
    }

    buf = malloc(TT_CMAP_FORMAT_6_SUBTABLE_SIZE(entryCount));
    if( NULL == buf ) {
        return FAILURE;
    }

    if( read_ngoback(fd, offset, buf, TT_CMAP_FORMAT_6_SUBTABLE_SIZE(entryCount)) < 0 ) {
        free(buf);
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Allocate and save in buf the cmap format 12 table.
 * 
 * @param fd File to get the table from.
 * @param offset Offset in file locating the table.
 * @param buf The buffer to allocate the data to.
 * @return 0 on succes. Negative integer on Fail.
 */
int get_format12_table(int fd, off_t offset, char *buf) {

    uint32_t length;
    if( read_ngoback(fd, offset + LENGTH_OFFSET, &length, sizeof(uint32_t)) < 0 ) {
        return FAILURE;
    }

    buf = malloc(length);
    if( NULL == buf ) {
        return FAILURE;
    }

    if( read_ngoback(fd, offset, buf, length) < 0 ) {
        free(buf);
        return FAILURE;
    }

    return SUCCESS;
}

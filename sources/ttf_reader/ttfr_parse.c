#include <ttf_reader.h>
#include "ttfr_parse.h"

#include <memory.h>
#include <stdint.h>

#define UNSUPPORTED_PLATFORM -2
#define UNSUPPORTED_FORMAT -3

/**
 * @brief Performs check if variable/command returns negative value.
 * 
 */
#define NEGATIVE_CHECK(command) if( command < 0 ) { return FAILURE; }


/**
 * @brief Performs check if variable/command is NULL.
 * 
 */
#define NULL_CHECK(command) if( NULL == command ) { return FAILURE; }

/**
 * @brief Reads 16 bits from fd to buf and saves changed endian to dest.
 * 
 */
#define READ_16(fd, buf, dest)                          \
    NEGATIVE_CHECK(read(fd, &buf, sizeof(uint16_t)))    \
    ENDIAN_SWITCH_16(dest, buf)

/**
 * @brief Reads 16 bits from fd to buf and saves changed endian to dest(without check).
 * 
 */
#define READ_16_NO_CHECK(fd, buf, dest)                 \
    read(fd, &buf, sizeof(uint16_t))                    \
    ENDIAN_SWITCH_16(dest, buf)

/**
 * @brief Reads 32 bits from fd to buf and saves changed endian to dest.
 * 
 */
#define READ_32(fd, buf, dest)                          \
    NEGATIVE_CHECK(read(fd, &buf, sizeof(uint32_t)))    \
    ENDIAN_SWITCH_32(dest, buf)

/**
 * @brief Reads 64 bits from fd to buf and saves changed endian to dest.
 * 
 */
#define READ_64(fd, buf, dest)                          \
    NEGATIVE_CHECK(read(fd, &buf, sizeof(uint64_t)))    \
    ENDIAN_SWITCH_64(dest, buf)

/**
 * @brief Reads 8 bits from fd to buf and saves to dest.
 * 
 */
#define READ_8(fd, dest)                                \
    NEGATIVE_CHECK(read(fd, &dest, sizeof(uint8_t)))

/**
 * @brief Reads the offset table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param offset_table the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int read_offset_table(int fd, TT_OFFSET_TABLE *offset_table) {

    uint32_t buf_32;
    uint16_t buf_16;

    READ_32(fd, buf_32, offset_table->scalarType);
    READ_16(fd, buf_16, offset_table->numTables);
    READ_16(fd, buf_16, offset_table->searchRange);
    READ_16(fd, buf_16, offset_table->entrySelector);
    READ_16(fd, buf_16, offset_table->rangeShift);
    return SUCCESS;
}

/**
 * @brief Reads the directory table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param directory_table the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int read_directory_table(int fd, TT_DIRECTORY_TABLE *directory_table) {

    uint32_t buf_32;

    READ_32(fd, buf_32, directory_table->tag);
    READ_32(fd, buf_32, directory_table->checkSum);
    READ_32(fd, buf_32, directory_table->offset);
    READ_32(fd, buf_32, directory_table->length);
    return SUCCESS;
}

/**
 * @brief Reads the head table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param head_table the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int read_head_table(int fd, off_t offset, TT_HEAD_TABLE *head_table) {

    uint64_t buf_64;
    uint32_t buf_32;
    uint16_t buf_16;

    NEGATIVE_CHECK(read_at_offset(fd, offset, &buf_32, sizeof(uint32_t)));
    ENDIAN_SWITCH_32(head_table->version, buf_32);

    READ_32(fd, buf_32, head_table->fontRevision);
    READ_32(fd, buf_32, head_table->checkSumAdjustment);
    READ_32(fd, buf_32, head_table->magicNumber);
    READ_16(fd, buf_16, head_table->flags);
    READ_16(fd, buf_16, head_table->unitsPerEm);
    READ_64(fd, buf_64, head_table->created);
    READ_64(fd, buf_64, head_table->modified);
    READ_16(fd, buf_16, head_table->xMin);
    READ_16(fd, buf_16, head_table->yMin);
    READ_16(fd, buf_16, head_table->xMax);
    READ_16(fd, buf_16, head_table->yMax);
    READ_16(fd, buf_16, head_table->macStyle);
    READ_16(fd, buf_16, head_table->lowestRecPPEM);
    READ_16(fd, buf_16, head_table->fontDirectionHint);
    READ_16(fd, buf_16, head_table->indexToLocFormat);
    READ_16(fd, buf_16, head_table->glyphDataFormat);
    return SUCCESS;
}

/**
 * @brief Reads the maxp table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param maxp_table the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int read_maxp_table(int fd, off_t offset, TT_MAXP_TABLE *maxp_table) {

    uint32_t buf_32;
    uint16_t buf_16;

    NEGATIVE_CHECK(read_at_offset(fd, offset, &buf_32, sizeof(uint32_t)));
    ENDIAN_SWITCH_32(maxp_table->version, buf_32);

    READ_16(fd, buf_16, maxp_table->numGlyphs);
    READ_16(fd, buf_16, maxp_table->maxPoints);
    READ_16(fd, buf_16, maxp_table->maxContours);
    READ_16(fd, buf_16, maxp_table->maxComponentPoints);
    READ_16(fd, buf_16, maxp_table->maxComponentContours);
    READ_16(fd, buf_16, maxp_table->maxZones);
    READ_16(fd, buf_16, maxp_table->maxTwilightPoints);
    READ_16(fd, buf_16, maxp_table->maxStorage);
    READ_16(fd, buf_16, maxp_table->maxFunctionDefs);
    READ_16(fd, buf_16, maxp_table->maxInstructionDefs);
    READ_16(fd, buf_16, maxp_table->maxStackElements);
    READ_16(fd, buf_16, maxp_table->maxSizeOfInstructions);
    READ_16(fd, buf_16, maxp_table->maxComponentElements);
    READ_16(fd, buf_16, maxp_table->maxComponentDepth);
    return SUCCESS;
}

/**
 * @brief Reads the loca table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param loca_table The table to save the data to.
 * @param indexToLocFormat The type of the loca table.
 * @param numGlyphs Number of glyphs in the font.
 * @return 0 on succes, -1 on failure.
 */
int read_loca_table(int fd, off_t offset, TT_LOCA_TABLE *loca_table, int16_t indexToLocFormat, uint16_t numGlyphs) {

    uint32_t buf_32;
    uint16_t buf_16;

    if( indexToLocFormat ) {

        loca_table->offsets_32 = malloc(sizeof(uint32_t)*numGlyphs);

        NEGATIVE_CHECK(read_at_offset(fd, offset, &buf_32, sizeof(uint32_t)));
        ENDIAN_SWITCH_32(loca_table->offsets_32[0], buf_32);

        for(uint16_t locai = 1; locai < numGlyphs; locai++) {
            READ_32(fd, buf_32, loca_table->offsets_32[locai]);
        }

    } else {

        loca_table->offsets_16 = malloc(sizeof(uint16_t)*numGlyphs);

        NEGATIVE_CHECK(read_at_offset(fd, offset, &buf_16, sizeof(uint16_t)));
        ENDIAN_SWITCH_16(loca_table->offsets_16[0], buf_16);

        for(uint16_t locai = 1; locai < numGlyphs; locai++) {
            READ_16(fd, buf_16, loca_table->offsets_16[locai]);
        }
        
    }

    return SUCCESS;
}

/**
 * @brief Reads the cmap table from file.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param cmap_table the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int _read_cmap_table(int fd, off_t offset, TT_CMAP_TABLE *cmap_table) {

    uint16_t buf_16;

    NEGATIVE_CHECK(read_at_offset(fd, offset, &buf_16, sizeof(uint16_t)));
    ENDIAN_SWITCH_16(cmap_table->version, buf_16);

    READ_16(fd, buf_16, cmap_table->numberSubtables);
    return SUCCESS;
}

/**
 * @brief Reads the cmap subtable from file.
 * 
 * @param fd The file descriptor.
 * @param cmap_subtable the table to save the data to.
 * @return 0 on succes, -1 on failure.
 */
int _read_cmap_subtable(int fd, TT_CMAP_SUBTABLE *cmap_subtable) {

    uint32_t buf_32;
    uint16_t buf_16;

    READ_16(fd, buf_16, cmap_subtable->platformID);
    READ_16(fd, buf_16, cmap_subtable->platformSpecificID);
    READ_32(fd, buf_32, cmap_subtable->offset);
    return SUCCESS;
}

int _read_format0_table(int fd, ttf_data *data) {

    TT_CMAP_FORMAT_0_SUBTABLE table_buf;
    uint16_t buf_16;

    data->cmap_table_format = malloc(sizeof(TT_CMAP_FORMAT_0_SUBTABLE));
    NULL_CHECK(data->cmap_table_format)

    READ_16(fd, buf_16, table_buf.format);
    READ_16(fd, buf_16, table_buf.length);
    READ_16(fd, buf_16, table_buf.language);

    for(uint8_t glyfi = 0; glyfi < UINT8_MAX + 1; glyfi++) {
        READ_8(fd, table_buf.glyphIndexArray[glyfi]);
    }

    memcpy(data->cmap_table_format, &table_buf, sizeof(TT_CMAP_FORMAT_0_SUBTABLE));

    return SUCCESS;
}

int __read_array_16(int fd, uint16_t *arr, size_t length) {

    uint16_t buf_16;

    for( size_t i = 0; i < length; i++ ) {
        READ_16(fd, buf_16, arr[i]);
    }

    return SUCCESS;
}

int _read_format4_table(int fd, ttf_data *data) {

    TT_CMAP_FORMAT_4_SUBTABLE table_buf;
    uint16_t buf_16, segCount, *endCode, *startCode, *idDelta, *idRangeOffset;

    READ_16(fd, buf_16, table_buf.format);
    READ_16(fd, buf_16, table_buf.length);
    READ_16(fd, buf_16, table_buf.language);
    READ_16(fd, buf_16, table_buf.segCountX2);
    READ_16(fd, buf_16, table_buf.searchRange);
    READ_16(fd, buf_16, table_buf.entrySelector);
    READ_16(fd, buf_16, table_buf.rangeShift);

    data->cmap_table_format = malloc(sizeof(TT_CMAP_FORMAT_4_SUBTABLE));
    NULL_CHECK(data->cmap_table_format)
    
    segCount = table_buf.segCountX2 >> 1;

    table_buf.endCode = (uint16_t *)malloc(sizeof(uint16_t)*segCount);
    table_buf.startCode = (uint16_t *)malloc(sizeof(uint16_t)*segCount);
    table_buf.idDelta = (uint16_t *)malloc(sizeof(uint16_t)*segCount);
    table_buf.idRangeOffset = (uint16_t *)malloc(sizeof(uint16_t)*segCount);

    if( NULL == table_buf.endCode || NULL == table_buf.startCode || NULL == table_buf.idDelta || NULL == table_buf.idRangeOffset ) {
        free(table_buf.endCode);
        free(table_buf.startCode);
        free(table_buf.idDelta);
        free(table_buf.idRangeOffset);
        free(data->cmap_table_format);
        return FAILURE;
    }

    // the inside read of reservedPad doesn't need endian conversion
    // because it should be 0 anywa => No READ_16 is needed.
    if( __read_array_16(fd, table_buf.endCode, segCount) < 0 ||
            read(fd, &table_buf.reservedPad, sizeof(uint16_t)) < 0 ||
            __read_array_16(fd, table_buf.startCode, segCount) < 0 ||
            __read_array_16(fd, table_buf.idDelta, segCount) < 0 ||
            __read_array_16(fd, table_buf.idRangeOffset, segCount) < 0 ||
            __read_array_16(fd, table_buf.glyphIndexArray, UINT16_MAX + 1) < 0 ) {
        free(table_buf.endCode);
        free(table_buf.startCode);
        free(table_buf.idDelta);
        free(table_buf.idRangeOffset);
        free(data->cmap_table_format);
        return FAILURE;
    }

    memcpy(data->cmap_table_format, &table_buf, sizeof(TT_CMAP_FORMAT_4_SUBTABLE));

    return SUCCESS;
}

int _read_format6_table(int fd, ttf_data *data) {

    TT_CMAP_FORMAT_6_SUBTABLE table_buf;
    uint16_t buf_16;

    READ_16(fd, buf_16, table_buf.format);
    READ_16(fd, buf_16, table_buf.length);
    READ_16(fd, buf_16, table_buf.language);
    READ_16(fd, buf_16, table_buf.firstCode);
    READ_16(fd, buf_16, table_buf.entryCount);

    data->cmap_table_format = malloc(sizeof(TT_CMAP_FORMAT_6_SUBTABLE));
    NULL_CHECK(data->cmap_table_format)

    table_buf.glyphIndexArray = (uint16_t *)malloc(sizeof(uint16_t)*table_buf.entryCount);

    if( NULL == table_buf.glyphIndexArray ) {
        free(data->cmap_table_format);
        return FAILURE;
    }

    if( __read_array_16(fd, table_buf.glyphIndexArray, table_buf.entryCount) < 0 ) {
        free(table_buf.glyphIndexArray);
        free(data->cmap_table_format);
        return FAILURE;
    }

    memcpy(data->cmap_table_format, &table_buf, sizeof(TT_CMAP_FORMAT_6_SUBTABLE));

    return SUCCESS;
}

int __read_group_f12(int fd, uint32_t *arr_1, uint32_t *arr_2, uint32_t *arr_3, size_t groupi) {

    uint32_t buf_32;

    READ_32(fd, buf_32, arr_1[groupi]);
    READ_32(fd, buf_32, arr_2[groupi]);
    READ_32(fd, buf_32, arr_3[groupi]);

    return SUCCESS;
}

int _read_format12_table(int fd, ttf_data *data) {

    TT_CMAP_FORMAT_12_SUBTABLE_EDITED table_buf;
    uint32_t buf_32;
    uint16_t buf_16;

    READ_16(fd, buf_16, table_buf.format);
    READ_16(fd, buf_16, table_buf.reserved);
    READ_32(fd, buf_32, table_buf.length);
    READ_32(fd, buf_32, table_buf.language);
    READ_32(fd, buf_32, table_buf.nGroups);

    data->cmap_table_format = malloc(sizeof(TT_CMAP_FORMAT_12_SUBTABLE_EDITED));
    NULL_CHECK(data->cmap_table_format)

    table_buf.startCharCode = malloc(sizeof(uint32_t)*table_buf.nGroups);
    table_buf.endCharCode = malloc(sizeof(uint32_t)*table_buf.nGroups);
    table_buf.startGlyphCode = malloc(sizeof(uint32_t)*table_buf.nGroups);

    if( NULL == table_buf.startCharCode || NULL == table_buf.endCharCode || NULL == table_buf.startGlyphCode ) {
        free(table_buf.startCharCode);
        free(table_buf.endCharCode);
        free(table_buf.startGlyphCode);
        free(data->cmap_table_format);
        return FAILURE;
    }

    for( uint32_t groupi = 0; groupi < table_buf.nGroups; groupi++ ) {
        if( __read_group_f12(fd, table_buf.startCharCode, table_buf.endCharCode, table_buf.startGlyphCode, groupi) < 0 ) {
            free(table_buf.startCharCode);
            free(table_buf.endCharCode);
            free(table_buf.startGlyphCode);
            free(data->cmap_table_format);
            return FAILURE;
        }
    }

    memcpy(data->cmap_table_format, &table_buf, sizeof(TT_CMAP_FORMAT_12_SUBTABLE_EDITED));

    return SUCCESS;
}

/**
 * @brief Reads the information of the cmap table saved in the ttf_data struct.
 * 
 * @param fd The file descriptor.
 * @param offset Offset of the offset table.
 * @param data Pointer tor structure where cmap data is saved.
 * @return 0 on succes, -1 on failure, -2 on platform missmatch
 */
int read_cmap_table(int fd, off_t offset, ttf_data *data) {

    uint32_t buf_32;
    uint16_t buf_16, cmap_format;

    TT_CMAP_TABLE cmap_table;
    TT_CMAP_SUBTABLE cmap_subtable;

    NEGATIVE_CHECK(_read_cmap_table(fd, offset, &cmap_table))

    for( uint16_t cmapi = 0; cmapi < cmap_table.numberSubtables; cmapi++ ) {

        NEGATIVE_CHECK(_read_cmap_subtable(fd, &cmap_subtable))

        if( cmap_subtable.platformID == 0 ) {
            break;
        }
    }

    if( cmap_subtable.platformID != 0 ) {
        return UNSUPPORTED_PLATFORM;
    }

    NEGATIVE_CHECK(read_n_stayback(fd, offset + cmap_subtable.offset, &buf_16, sizeof(uint16_t)));
    ENDIAN_SWITCH_16(cmap_format, buf_16);

    data->cmap_format = (uint8_t)cmap_format;
    
    if( !SUPPORTED_FORMAT(cmap_format) ) {
        return UNSUPPORTED_FORMAT;
    }

    switch (cmap_format)
    {
    case CMAP_FORMAT_0:
        NEGATIVE_CHECK(_read_format0_table(fd, data))
        break;
    case CMAP_FORMAT_4:
        NEGATIVE_CHECK(_read_format4_table(fd, data))
        break;
    case CMAP_FORMAT_6:
        NEGATIVE_CHECK(_read_format6_table(fd, data))
        break;
    case CMAP_FORMAT_12:
        NEGATIVE_CHECK(_read_format12_table(fd, data))
        break;
    default:
        break;
    }

    return SUCCESS;
}

/**
 * @brief Function read() but reads from the offset and stays at the offset passed.
 * 
 * @param fd File descyptor to read from.
 * @param offset The offset relative to the begining of the file.
 * @param buf The buffer to save data to.
 * @param nbytes Number of bytes to read.
 * @return Same as read() except lseek failure than -1.
 */
int read_n_stayback(int fd, off_t offset, void *buf, size_t nbytes) {
    size_t rbytes;

    if( lseek(fd, offset, SEEK_SET) < 0 ) {
        return FAILURE;
    }

    if( (rbytes = read(fd, buf, nbytes)) < 0 ) {
        return FAILURE;
    }

    if( lseek(fd, offset, SEEK_SET) < 0 ) {
        return FAILURE;
    }
    
    return rbytes;
}

/**
 * @brief Function read() but reads from the offset.
 * 
 * @param fd File descyptor to read from.
 * @param offset The offset relative to the begining of the file.
 * @param buf The buffer to save data to.
 * @param nbytes Number of bytes to read.
 * @return Same as read() except lseek failure than -1.
 */
int read_at_offset(int fd, off_t offset, void *buf, size_t nbytes) {
    size_t rbytes;

    if( lseek(fd, offset, SEEK_SET) < 0 ) {
        return FAILURE;
    }

    if( (rbytes = read(fd, buf, nbytes)) < 0 ) {
        return FAILURE;
    }
    
    return rbytes;
}

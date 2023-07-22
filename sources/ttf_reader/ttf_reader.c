#include <ttf_reader.h>
#include "ttfr_parse.h"
#include "ttfr_check.h"

/**
 * @brief Create a ttf data object
 * 
 * @param data The object reference to write the data to.
 * @param ttf_file_path Path of the ttf file to open.
 * @return 0 on success. negativ intiger on failure.
 */
int create_ttf_data(ttf_data *data, const char *ttf_file_path) {

    int ttf_fd = open(ttf_file_path, O_RDONLY);
    if( ttf_fd < 0 ) {
        return FILE_OPEN_FAIL;
    }

    TT_OFFSET_TABLE offset_table;
    TT_DIRECTORY_TABLE directory_table, head_directory_table, maxp_directory_table, loca_directory_table, cmap_directory_table, glyf_directory_table;

    if( read_offset_table(ttf_fd, &offset_table) < 0 ) {
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    if( !(offset_table.scalarType == TRUE_SCALAR_0 || offset_table.scalarType == TRUE_SCALAR_1) ) {
        CLOSE_RETURN(ttf_fd) NO_SUPPORTED_SCALAR_TYPE;
    }

    uint8_t found_count = 0;
    // TODO: Implement division into binary search on condition  offset_table.numTables > LINEAR_SEARCH_LIMIT
    for( uint16_t tablei = 0; tablei < offset_table.numTables; tablei++ ) {

        if( NUM_MANDATORY_TABLES == found_count ) {
            break;
        }

        if( read_directory_table(ttf_fd, &directory_table) < 0 ) {
            CLOSE_RETURN(ttf_fd) READ_FAIL;
        }

        if(!SEARCHED_TAG(directory_table.tag)) {
            continue;
        }

        switch (directory_table.tag) {
        case HEAD_TAG:
            head_directory_table = directory_table;
            found_count++;
            break;

        case MAXP_TAG:
            maxp_directory_table = directory_table;
            found_count++;
            break;

        case LOCA_TAG:
            loca_directory_table = directory_table;
            found_count++;
            break;

        case CMAP_TAG:
            cmap_directory_table = directory_table;
            found_count++;
            break;

        case GLYF_TAG:
            glyf_directory_table = directory_table;
            found_count++;
            break;
        
        default:
            break;
        }
    }

    if( found_count != NUM_MANDATORY_TABLES ) {
        CLOSE_RETURN(ttf_fd) MISSING_MANDATORY_TABLE;
    }

    // head & maxp
    if( read_head_table(ttf_fd, head_directory_table.offset, &data->head_table) < 0 |
            read_maxp_table(ttf_fd, maxp_directory_table.offset, &data->maxp_table) < 0 ) {
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    // loca
    if( read_loca_table(ttf_fd, loca_directory_table.offset, &data->loca_table, data->head_table.indexToLocFormat, data->maxp_table.numGlyphs) < 0 ) {
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    // glyf
    data->glyf_table_raw = malloc(glyf_directory_table.length);
    if( NULL == data->glyf_table_raw ) {
        FREE_TT_LOCA_TABLE(data->loca_table);
        CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
    }

    if( read_at_offset(ttf_fd, glyf_directory_table.offset, data->glyf_table_raw, glyf_directory_table.length) < 0 ) {
        FREE_TT_LOCA_TABLE(data->loca_table);
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    // cmap
    int cmap_read_returned = 0;
    if( (cmap_read_returned = read_cmap_table(ttf_fd, cmap_directory_table.offset, data) ) < 0 ) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) cmap_read_returned;
    }

    return SUCCESS;
}

/**
 * @brief Get the index for locating glyf from format 0 cmap subtable.
 * 
 * @param data Font data.
 * @param chr The char to locate.
 * @return The index. Negative on failure.
 */
int16_t get_index_f0(ttf_data *data, char chr) {
    int16_t char_conv = (int16_t)chr;
    if( char_conv > UINT8_MAX || char_conv < 0 ) {
        return MISSING_GLYPH;
    }
    return ((TT_CMAP_FORMAT_0_SUBTABLE*)data->cmap_table_format)->glyphIndexArray[char_conv];
}

/**
 * @brief Get the index for locating glyf from format 4 cmap subtable.
 * 
 * @param data Font data.
 * @param chr The char to locate.
 * @return The index. Negative on failure.
 */
int32_t get_index_f4(ttf_data *data, char chr) {
    int32_t char_conv = (int32_t)chr;
    if( char_conv > UINT16_MAX || char_conv < 0 ) {
        return MISSING_GLYPH;
    }
    TT_CMAP_FORMAT_4_SUBTABLE *cmap_table = (TT_CMAP_FORMAT_4_SUBTABLE*)data->cmap_table_format;
    uint16_t segCount = cmap_table->segCountX2 >> 1, segi, gindex;
    
    // binary search is not performed as the library operates mostly on ascii
    // because of that linear search will almost always and very quickly even with huge glyph collections
    for(segi = 0; segi < segCount; segi++) {
        if( cmap_table->endCode[segi] >= char_conv ) {
            if( cmap_table->startCode[segi] > char_conv ) {
                return MISSING_GLYPH;
            }
            break;
        }
    }

    if( 0 == cmap_table->idRangeOffset[segi] ) {
        gindex = cmap_table->idDelta[segi] + char_conv;
    } else {
        gindex = *(&cmap_table->idRangeOffset[segi] + cmap_table->idRangeOffset[segi] / 2 + (char_conv - cmap_table->startCode[segi]));
    }
    return cmap_table->glyphIndexArray[gindex];
}

/**
 * @brief Get the index for locating glyf from format 6 cmap subtable.
 * 
 * @param data Font data.
 * @param chr The char to locate.
 * @return The index. Negative on failure.
 */
int32_t get_index_f0(ttf_data *data, char chr) {
    int32_t char_conv = (int32_t)chr;
    if( char_conv > UINT16_MAX || char_conv < 0 ) {
        return MISSING_GLYPH;
    }
    return ((TT_CMAP_FORMAT_0_SUBTABLE*)data->cmap_table_format)->glyphIndexArray[char_conv];
}

/**
 * @brief Checks if font contains needed alphabet.
 * 
 * @param data The font data.
 * @param alphabet The alphabet.
 * @return int 0 on success, negative integer on failure.
 */
int alphabet_inclusion_check(ttf_data *data, const char *alphabet) {

    size_t alphabet_len = strlen(alphabet);

    switch (data->cmap_format)
    {
    case CMAP_FORMAT_0:
        for(size_t chari = 0; chari < alphabet_len; chari++) {
            if( ttf_includes_f0(data, alphabet[chari]) < 0 ) {
                return FAILURE;
            }
        }
        break;
    case CMAP_FORMAT_4:
        for(size_t chari = 0; chari < alphabet_len; chari++) {
            if( ttf_includes_f4(data, alphabet[chari]) < 0 ) {
                return FAILURE;
            }
        }
        break;
    case CMAP_FORMAT_6:
        for(size_t chari = 0; chari < alphabet_len; chari++) {
            if( ttf_includes_f6(data, alphabet[chari]) < 0 ) {
                return FAILURE;
            }
        }
        break;
    case CMAP_FORMAT_12:
        for(size_t chari = 0; chari < alphabet_len; chari++) {
            if( ttf_includes_f12(data, alphabet[chari]) < 0 ) {
                return FAILURE;
            }
        }
        break;
    default:
        return NO_SUPPORTED_CMAP_FORMAT;
    }
    return SUCCESS;
}

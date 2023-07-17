#include <ttf_reader.h>
#include "ttfr_funcs.h"

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
    TT_DIRECTORY_TABLE directory_table, loca_directory_table, cmap_directory_table, glyf_directory_table;

    if( read(ttf_fd, &offset_table, sizeof(TT_OFFSET_TABLE)) < 0 ) {
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    off_t file_pos_buf;
    // TODO: Implement division into binary search on condition  offset_table.numTables > LINEAR_SEARCH_LIMIT
    for( size_t tablei = 0; tablei < offset_table.numTables; tablei++ ) {

        if( read(ttf_fd, &directory_table, sizeof(TT_DIRECTORY_TABLE)) < 0 ) {
            CLOSE_RETURN(ttf_fd) READ_FAIL;
        }

        if(!SEARCHED_TAG(directory_table.tag)) {
            continue;
        }

        switch (directory_table.tag)
        {
        case HEAD_TAG:

            if( read_ngoback(ttf_fd, directory_table.offset, &data->head_table, sizeof(TT_HEAD_TABLE)) < 0 ) {
                CLOSE_RETURN(ttf_fd) READ_FAIL;
            }
            break;

        case MAXP_TAG:
            if( read_ngoback(ttf_fd, directory_table.offset, &data->maxp_table, sizeof(TT_MAXP_TABLE)) < 0 ) {
                CLOSE_RETURN(ttf_fd) READ_FAIL;
            }
            break;

        case LOCA_TAG:
            loca_directory_table = directory_table;
            break;

        case CMAP_TAG:
            cmap_directory_table = directory_table;
            break;

        case GLYF_TAG:
            glyf_directory_table = directory_table;
            break;
        
        default:
            break;
        }
    }

    // data.head_table and data.maxp_table are correctly filled now -> fill the cmap, loca and glyf data
    // loca
    if(data->head_table.indexToLocFormat) {
        data->loca_table.offsets_32 = (uint32_t*)malloc(sizeof(uint32_t) * data->maxp_table.numGlyphs);
        if( NULL == data->loca_table.offsets_32 ) {
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        if( read_ngoback(ttf_fd, loca_directory_table.offset, &data->loca_table.offsets_32, sizeof(uint32_t) * data->maxp_table.numGlyphs) < 0 ) {
                free(data->loca_table.offsets_32);
                CLOSE_RETURN(ttf_fd) READ_FAIL;
        }
        data->loca_table.offsets_16 = NULL;
    } else {
        data->loca_table.offsets_16 = (uint16_t*)malloc(sizeof(uint16_t) * data->maxp_table.numGlyphs);
        if( NULL == data->loca_table.offsets_16 ) {
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        if( read_ngoback(ttf_fd, loca_directory_table.offset, &data->loca_table.offsets_16, sizeof(uint16_t) * data->maxp_table.numGlyphs) < 0 ) {
                free(data->loca_table.offsets_16);
                CLOSE_RETURN(ttf_fd) READ_FAIL;
        }
        data->loca_table.offsets_32 = NULL;
    }

    //glyf
    data->glyf_table_raw = malloc(glyf_directory_table.length);
    if( NULL == data->glyf_table_raw ) {
        FREE_TT_LOCA_TABLE(data->loca_table);
        CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
    }

    if( read_ngoback(ttf_fd, glyf_directory_table.offset, data->glyf_table_raw, glyf_directory_table.length) < 0 ) {
        FREE_TT_LOCA_TABLE(data->loca_table);
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    //cmap
    TT_CMAP_TABLE cmap_table;
    TT_CMAP_SUBTABLE cmap_subtable, cmap_subtable_buf;
    uint8_t found_supported = 0;

    if( lseek(ttf_fd, cmap_directory_table.offset, SEEK_SET) < 0 ) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) SEEK_FAIL;
    }

    if( read(ttf_fd, &cmap_table, sizeof(TT_CMAP_TABLE)) < 0 ) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    // additional version check
    if( 0 == cmap_table.version ) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) FAILURE;
    }

    for(uint16_t subtablei = 0; subtablei < cmap_table.numberSubtables; subtablei++) {
        if( read(ttf_fd, &cmap_subtable_buf, sizeof(TT_CMAP_SUBTABLE)) < 0 ) {
            FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
            CLOSE_RETURN(ttf_fd) READ_FAIL;
        }

        // remember the supported configuration
        if( 0 == cmap_subtable_buf.platformID && 0 == cmap_subtable_buf.platformSpecificID ) {
            cmap_subtable = cmap_subtable_buf;
            found_supported = 1;
        }
    }

    if(!found_supported) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) NO_SUPPORTED_PLATFORM;
    }

    uint16_t cmap_format_buf;
    if( read_ngoback(ttf_fd, cmap_subtable.offset, &cmap_format_buf, sizeof(uint16_t)) < 0 ) {
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) READ_FAIL;
    }

    data->cmap_format = (uint8_t)cmap_format_buf;

    switch (data->cmap_format) {
    case CMAP_FORMAT_0:
        if( get_format0_table(ttf_fd, cmap_subtable.offset, data->cmap_table_format_raw) < 0 ) {
            FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        break;

    case CMAP_FORMAT_4:
        if( get_format4_table(ttf_fd, cmap_subtable.offset, data->cmap_table_format_raw) < 0 ) {
            FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        break;

    case CMAP_FORMAT_6:
        if( get_format6_table(ttf_fd, cmap_subtable.offset, data->cmap_table_format_raw) < 0 ) {
            FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        break;

    case CMAP_FORMAT_12:
        if( get_format12_table(ttf_fd, cmap_subtable.offset, data->cmap_table_format_raw) < 0 ) {
            FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
            CLOSE_RETURN(ttf_fd) ALLOC_FAIL;
        }
        break;
    
    default:
        FREE_LOCA_N_GLYF_TABLES(data->loca_table, data->glyf_table_raw);
        CLOSE_RETURN(ttf_fd) NO_SUPPORTED_CMAP_FORMAT;
        break;
    }

    return SUCCESS;
}
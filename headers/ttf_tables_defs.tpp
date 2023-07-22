#include <stdint.h>

typedef uint32_t Fixed;
typedef int64_t longDateTime;
typedef int16_t FWord;

// free macros
#define FREE_TT_LOCA_TABLE(table) \
    if( NULL == table.offsets_16 ) { free(table.offsets_32); } \
    else { free(table.offsets_16); }

#define FREE_TT_GLYF_TABLE_RAW(table) free(table)

#define FREE_LOCA_N_GLYF_TABLES(loca, glyf) \
    FREE_TT_LOCA_TABLE(loca);               \
    FREE_TT_GLYF_TABLE_RAW(glyf);

// tag: offset
typedef struct _TT_OFFSET_TABLE {
    uint32_t scalarType;
    uint16_t numTables;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
}TT_OFFSET_TABLE;
// end offset

// tag: directory
typedef struct _TT_DIRECTORY_TABLE {
    uint32_t tag;
    uint32_t checkSum;
    uint32_t offset; // from the begining of the file
    uint32_t length;
}TT_DIRECTORY_TABLE;
// end directory

// tag: 'head'
typedef struct _TT_HEAD_TABLE {
    Fixed version;
    Fixed fontRevision;
    uint32_t checkSumAdjustment;
    uint32_t magicNumber;
    uint16_t flags;
    uint16_t unitsPerEm;
    longDateTime created;
    longDateTime modified;
    FWord xMin;
    FWord yMin;
    FWord xMax;
    FWord yMax;
    uint16_t macStyle;
    uint16_t lowestRecPPEM;
    int16_t fontDirectionHint;
    int16_t indexToLocFormat;
    int16_t glyphDataFormat;
}TT_HEAD_TABLE;
// end 'head'

// tag: 'maxp'
typedef struct _TT_MAXP_TABLE {
    Fixed version;
    uint16_t numGlyphs;
    uint16_t maxPoints;
    uint16_t maxContours;
    uint16_t maxComponentPoints;
    uint16_t maxComponentContours;
    uint16_t maxZones;
    uint16_t maxTwilightPoints;
    uint16_t maxStorage;
    uint16_t maxFunctionDefs;
    uint16_t maxInstructionDefs;
    uint16_t maxStackElements;
    uint16_t maxSizeOfInstructions;
    uint16_t maxComponentElements;
    uint16_t maxComponentDepth;
}TT_MAXP_TABLE;
// end 'maxp'

// tag: 'loca'
typedef struct _TT_LOCA_TABLE {
    uint16_t* offsets_16; // offsets[n] - where n is the number of glyphs depending on 'maxp' table
    uint32_t* offsets_32; // 16/32 is decided based on the 'indexToLocFormat' param of 'head' table
}TT_LOCA_TABLE;

// tag: 'cmap'
typedef struct _TT_CMAP_TABLE {
    uint16_t version;
    uint16_t numberSubtables;
}TT_CMAP_TABLE;

typedef struct _TT_CMAP_SUBTABLE {
    uint16_t platformID;
    uint16_t platformSpecificID;
    uint32_t offset;
}TT_CMAP_SUBTABLE;

typedef struct _TT_CMAP_FORMAT_0_SUBTABLE {
    uint16_t format;
    uint16_t length;
    uint16_t language;
    uint8_t glyphIndexArray[UINT8_MAX+1];
}TT_CMAP_FORMAT_0_SUBTABLE;

typedef struct _TT_CMAP_FORMAT_4_SUBTABLE {
    uint16_t format;
    uint16_t length;
    uint16_t language;
    uint16_t segCountX2;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
    uint16_t *endCode; //endCode[segCount]
    uint16_t reservedPad;
    uint16_t *startCode; //startCode[segCount]
    uint16_t *idDelta; //idDelta[segCount]
    uint16_t *idRangeOffset; //idRangeOffset[segCount]
    uint16_t glyphIndexArray[UINT16_MAX+1];
}TT_CMAP_FORMAT_4_SUBTABLE;

typedef struct _TT_CMAP_FORMAT_6_SUBTABLE {
    uint16_t format;
    uint16_t length;
    uint16_t language;
    uint16_t firstCode;
    uint16_t entryCount;
    uint16_t *glyphIndexArray; //glyphIndexArray[entryCount]
}TT_CMAP_FORMAT_6_SUBTABLE;

typedef struct _TT_CMAP_FORMAT_12_SUBTABLE {
    uint16_t format;
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    uint32_t nGroups;
}TT_CMAP_FORMAT_12_SUBTABLE;

typedef struct _TT_CMAP_FORMAT_12_SUBSUBTABLE {
    uint32_t startCharCode;
    uint32_t endCharCode;
    uint32_t startGlyphCode;
}TT_CMAP_FORMAT_12_SUBSUBTABLE;
// end 'cmap'

typedef struct _TT_CMAP_FORMAT_12_SUBTABLE_EDITED {
    uint16_t format;
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    uint32_t nGroups;
    uint32_t *startCharCode; // startCharCode[nGroups]
    uint32_t *endCharCode; // endCharCode[nGroups]
    uint32_t *startGlyphCode; // startGlyphCode[nGroups]
}TT_CMAP_FORMAT_12_SUBTABLE_EDITED;

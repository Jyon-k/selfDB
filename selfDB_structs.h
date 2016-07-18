#ifndef _ROW_H_
#define _ROW_H_

#include <iostream>
#include <cstdint>

const int PAGE_MAX_BYTE = 16*1024;       //16KB
const int SEG_MAX_RECS = 1*1024*1024;   //1M

using namespace std;

struct HeaderSeg{
    int currentRecords;
    int maxPages;
    int recordsPerPage;
};

struct HeaderPage{
    int recordBytes;
    int maxRecords;
    int currentRecords;
};

struct Row{
    void** columns;
};

struct Page{
    HeaderPage header;
    Row* record;
};

struct Segment{
    HeaderSeg header;
    Page** segmentPage;
};

struct Schema{
    char* name;
    char* type;
};

struct Table{
    char* tableName;
    //Row* rowTable;
    Segment* tableSegment;
    Schema* tableSchema;
    int colSize;
    int rowSize;
};

#endif

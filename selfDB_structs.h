#ifndef _ROW_H_
#define _ROW_H_

#include <iostream>
#include <cstdint>

using namespace std;

struct Header{
    int count;
    int size;
};

struct Row{
    void** columns;
};

struct Page{
    Header* header;
    Row* record;
};

struct Segment{
    Header* header;
    Page** segmentPage;
};

struct Schema{
    char* name;
    char* type;
};

struct Table{
    char* tableName;
    Row* rowTable;
    Segment* tableSegment;
    Schema* tableSchema;
    int colSize;
    int rowSize;
};

#endif

#include <iostream>
#include <fstream>
#include <cstring>

#include "selfDB_structs.h"

using namespace std;

void loadCSVwithSegment(ifstream &ifs, Table* table, int lineCount){
    int segmentCount = lineCount/SEG_MAX_RECS + 1;
    int recordSize = table->colSize * 4;
    int pageMaxRec = PAGE_MAX_BYTE/recordSize;
    int segMaxPages = SEG_MAX_RECS/pageMaxRec;
    table-> tableSegment = new Segment[segmentCount];
    for(int i = 0; i < segmentCount; ++i){
        table->tableSegment[i].header.maxPages = segMaxPages;
        table->tableSegment[i].segmentPage = new Page*[segMaxPages];
        table->tableSegment[i].header.maxPages = segMaxPages;
    }


    int colSize = table->colSize;

    for(int row = 0; row < lineCount; ++row){
        int curSegIndex = row/SEG_MAX_RECS;
        int curPageIndex = row%SEG_MAX_RECS;
        int curRecIndex = curPageIndex%pageMaxRec;
        Page* currentPage = table->tableSegment[curSegIndex].segmentPage[curPageIndex];
        currentPage = new Page;
        currentPage->record = new Row[pageMaxRec];

        currentPage->header.recordBytes = recordSize;
        currentPage->header.maxRecords = pageMaxRec;
        currentPage->header.currentRecords = curRecIndex+1;

        char delimeter;
        currentPage->record[curRecIndex].columns = new void*[colSize];
        Row currentRec = currentPage->record[curRecIndex];
        for(int col = 0; col < colSize; ++col){
            if(col){
                ifs >> delimeter;
            }
            if(!strcmp(table->tableSchema[col].type, "int")){
                currentRec.columns[col] = new uint32_t;
                ifs >> *(uint32_t*)(currentRec.columns[col]);
                cout << *(uint32_t*)(currentRec.columns[col])<<endl;
            }
            else if(!strcmp(table->tableSchema[col].type, "bigint")){
                currentRec.columns[col] = new uint64_t;
                ifs >> *(uint64_t*)(currentRec.columns[col]);
            }
            else if(!strcmp(table->tableSchema[col].type, "char")){
                currentRec.columns[col] = new char;
                ifs >> *(char*)(currentRec.columns[col]);
            }
            else if(!strcmp(table->tableSchema[col].type, "decimal")){
                currentRec.columns[col] = new float;
                ifs >> *(float*)(currentRec.columns[col]);
            }
            else if(!strcmp(table->tableSchema[col].type, "double")){
                currentRec.columns[col] = new double;
                ifs >> *(double*)(currentRec.columns[col]);
                cout << *(double*)(currentRec.columns[col])<<endl;
            }
        }
        table->tableSegment[curSegIndex].header.currentRecords = row+1;
    }
    table->rowSize = lineCount;
}

/*
void loadCSV(ifstream &ifs, Table* rowTable, int lineCount){

    Row* newTable = new Row[lineCount];

    int colSize = rowTable->colSize;

    char delimeter;
    for(int row = 0; row < lineCount; ++row){
        newTable[row].columns = new void*[rowTable->colSize];
        for(int col = 0; col < colSize; ++col){
            if(col){
                ifs >> delimeter;
            }
            if(!strcmp(rowTable->tableSchema[col].type, "int")){
                newTable[row].columns[col] = new uint32_t;
                ifs >>*(uint32_t*)(newTable[row].columns[col]);
            }
            else if(!strcmp(rowTable->tableSchema[col].type, "bigint")){
                newTable[row].columns[col] = new uint64_t;
                ifs >>*(uint64_t*)(newTable[row].columns[col]);
            }
            else if(!strcmp(rowTable->tableSchema[col].type, "char")){
                newTable[row].columns[col] = new char;
                ifs >>*(char*)(newTable[row].columns[col]);
            }
            else if(!strcmp(rowTable->tableSchema[col].type, "decimal")){
                newTable[row].columns[col] = new float;
                ifs >>*(float*)(newTable[row].columns[col]);
            }
            else if(!strcmp(rowTable->tableSchema[col].type, "double")){
                newTable[row].columns[col] = new double;
                ifs >>*(double*)(newTable[row].columns[col]);
            }

        }
    }

    rowTable->rowTable = newTable;
    rowTable->rowSize = lineCount;
    cout << "Load table " << rowTable->tableName << "!" << endl;
}
*/

#include <iostream>
#include <fstream>
#include <cstring>

#include "selfDB_structs.h"

using namespace std;

void loadCSVwithSegment(ifstream &ifs, Table* table, int lineCount){
    int segmentCount = lineCount/SEG_MAX_RECS + 1;
    int recordSize = table->colSize * 4;
    int pageMaxRec = PAGE_MAX_BYTE/recordSize+1;
    int segMaxPages = SEG_MAX_RECS/pageMaxRec+1;
    table-> tableSegment = new Segment[segmentCount];
    for(int i = 0; i < segmentCount; ++i){
        table->tableSegment[i].header.maxPages = segMaxPages;
        table->tableSegment[i].segmentPage = new Page*[segMaxPages];
        table->tableSegment[i].header.maxPages = segMaxPages;
    }


    int colSize = table->colSize;
    int curSegIndex = 0;
    int curPageIndex = 0;
    int prevPageIndex = -1;
    int curRecIndex = 0;
    Page* currentPage;

    char delimeter;


    for(int row = 0; row < lineCount; ++row){
        curSegIndex = row/SEG_MAX_RECS;
        curPageIndex = (row - curSegIndex * segMaxPages)/pageMaxRec;
        curRecIndex = row%pageMaxRec;

        if(curRecIndex == 0){
        //    cout << "******************" << segMaxPages << " : " << pageMaxRec << endl;
            table->tableSegment[curSegIndex].segmentPage[curPageIndex] = new Page;
            currentPage = table->tableSegment[curSegIndex].segmentPage[curPageIndex];
            currentPage->record = new Row[pageMaxRec];
            currentPage->header.recordBytes = recordSize;
            currentPage->header.maxRecords = pageMaxRec;
        }
        //cout << segMaxPages << " : " << pageMaxRec << " : " << curPageIndex << " : " << curRecIndex << endl;
        if(currentPage == NULL) cout << " DAMN " << endl;
        currentPage->header.currentRecords = curRecIndex+1;

        currentPage->record[curRecIndex].columns = new void*[colSize];
        Row currentRec = currentPage->record[curRecIndex];
        for(int col = 0; col < colSize; ++col){
            if(col){
                ifs >> delimeter;
            }
            if(!strcmp(table->tableSchema[col].type, "int")){
                currentRec.columns[col] = new uint32_t;
                ifs >> *(uint32_t*)(currentRec.columns[col]);
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
            }
        }
        table->tableSegment[curSegIndex].header.currentRecords = row+1;
        prevPageIndex = curPageIndex;
    }
    cout << segmentCount << " : " << segMaxPages << " : " << pageMaxRec << endl;
    cout << curSegIndex << " : " << curPageIndex << " : " << curRecIndex << endl;
    table->rowSize = lineCount;
    cout << table->tableName <<" is loaded. " << endl;
    cout << lineCount << " row(s)" << endl;
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

#include <iostream>
#include <fstream>
#include <cstring>

#include "selfDB_structs.h"

using namespace std;

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

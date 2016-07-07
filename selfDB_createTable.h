#include <iostream>
#include <fstream>
#include <cstring>
#include "selfDB_structs.h"

using namespace std;

Table* create(ifstream &ifs, const char* tableName, int lineCount){

    cout << "Create Table" << endl;

    //actually read the line
    Table* newRowTable = new Table;
    Row* newTable = new Row[lineCount];

    char delimeter;
    for(int row = 0; row < lineCount; ++row){
        ifs >> newTable[row].orderKey
            >> delimeter
            >> newTable[row].custKey
            >> delimeter
            >> newTable[row].totalPrice;
    }
    cout << "Table is created : " << lineCount << "row(s)" << endl;

    //newRowTable->tableName = tableName;
    newRowTable->tableName = new char[strlen(tableName) + 1];
    strcpy(newRowTable->tableName, tableName);
    newRowTable->rowTable = newTable;
    newRowTable->rowSize = lineCount;

    return newRowTable;
}

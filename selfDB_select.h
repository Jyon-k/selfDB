#include <iostream>
#include <cstring>

#include "selfDB_structs.h"

using namespace std;

void printColumn(Table* table, int row, int col){
    if(!strcmp(table->tableSchema[col].type, "int")){
        cout << *((uint32_t*)(table->rowTable[row].columns[col]));
    }
    else if(!strcmp(table->tableSchema[col].type, "bigint")){
        cout << *((uint64_t*)(table->rowTable[row].columns[col]));
    }
    else if(!strcmp(table->tableSchema[col].type, "char")){
        cout << *((char*)(table->rowTable[row].columns[col]));
    }
    else if(!strcmp(table->tableSchema[col].type, "decimal")){
        cout << *((float*)(table->rowTable[row].columns[col]));
    }
    else if(!strcmp(table->tableSchema[col].type, "double")){
        cout << *((double*)(table->rowTable[row].columns[col]));
    }
}

void selectAll(Table* table){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    for(int row = 0; row < rowSize; ++row){
        for(int col = 0; col < colSize; ++col){
            if(col) cout << "|";
            printColumn(table, row, col);
        }
        cout << endl;
        ++count;
    }

    cout << count << " row(s) selected" << endl;

    /*
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        cout << rowTable[row].orderKey << "|"
            << rowTable[row].custKey << "|"
            << rowTable[row].totalPrice << endl;
        ++count;
    }
    cout << count << " row(s) selected" << endl;
    */
}

void selectGreater(Table* table, const char* colName, const char*  operand){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    int selectedCol = -1;
    for(int col = 0; col < colSize; ++col){
        if(!strcmp(table->tableSchema[col].name, colName)){
            selectedCol = col;
            break;
        }
    }
    if(selectedCol < 0){
        cout << "No such column in table " << table->tableName << "!!" << endl;
    }

    for(int row = 0; row < rowSize; ++row){
        if(table->rowTable[row].columns[selectedCol] > (void*)operand){
            for(int col = 0; col < colSize; ++col){
                if(col) cout << "|";
                printColumn(table, row, col);
            }
            ++count;
        }
        cout << endl;
    }

    cout << count << " row(s) selected" << endl;

    /*
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        if(rowTable[row].totalPrice > operand){
            cout << rowTable[row].orderKey << "|"
                << rowTable[row].custKey << "|"
                << rowTable[row].totalPrice << endl;
            ++count;
        }
    }
    cout << count << " row(s) selected" << endl;
    */
}

void selectGreaterEqual(Table* table, const char* colName, const char* operand){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    int selectedCol = -1;
    for(int col = 0; col < colSize; ++col){
        if(!strcmp(table->tableSchema[col].name, colName)){
            selectedCol = col;
            break;
        }
    }
    if(selectedCol < 0){
        cout << "No such column in table " << table->tableName << "!!" << endl;
    }

    for(int row = 0; row < rowSize; ++row){
        if(table->rowTable[row].columns[selectedCol] >= (void*)operand){
            for(int col = 0; col < colSize; ++col){
                if(col) cout << "|";
                printColumn(table, row, col);
            }
            ++count;
        }
        cout << endl;
    }

    cout << count << " row(s) selected" << endl;

    /*
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        if(rowTable[row].totalPrice >= operand){
            cout << rowTable[row].orderKey << "|"
                << rowTable[row].custKey << "|"
                << rowTable[row].totalPrice << endl;
            ++count;
        }
    }
    cout << count << " row(s) selected" << endl;
    */
}

void selectLess(Table* table, const char* colName, const char*  operand){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    int selectedCol = -1;
    for(int col = 0; col < colSize; ++col){
        if(!strcmp(table->tableSchema[col].name, colName)){
            selectedCol = col;
            break;
        }
    }
    if(selectedCol < 0){
        cout << "No such column in table " << table->tableName << "!!" << endl;
    }

    for(int row = 0; row < rowSize; ++row){
        if(table->rowTable[row].columns[selectedCol] < (void*)operand){
            for(int col = 0; col < colSize; ++col){
                if(col) cout << "|";
                printColumn(table, row, col);
            }
            ++count;
        }
        cout << endl;
    }

    cout << count << " row(s) selected" << endl;

    /*
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        if(rowTable[row].totalPrice < operand){
            cout << rowTable[row].orderKey << "|"
                << rowTable[row].custKey << "|"
                << rowTable[row].totalPrice << endl;
            ++count;
        }
    }
    cout << count << " row(s) selected" << endl;
    */
}

void selectLessEqual(Table* table, const char* colName, const char* operand){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    int selectedCol = -1;
    for(int col = 0; col < colSize; ++col){
        if(!strcmp(table->tableSchema[col].name, colName)){
            selectedCol = col;
            break;
        }
    }
    if(selectedCol < 0){
        cout << "No such column in table " << table->tableName << "!!" << endl;
    }

    for(int row = 0; row < rowSize; ++row){
        if(table->rowTable[row].columns[selectedCol] <= (void*)operand){
            for(int col = 0; col < colSize; ++col){
                if(col) cout << "|";
                printColumn(table, row, col);
            }
            ++count;
        }
        cout << endl;
    }

    cout << count << " row(s) selected" << endl;

    /*
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        if(rowTable[row].totalPrice <= operand){
            cout << rowTable[row].orderKey << "|"
                << rowTable[row].custKey << "|"
                << rowTable[row].totalPrice << endl;
            ++count;
        }
    }
    cout << count << " row(s) selected" << endl;
    */
}

#include <iostream>
#include <cstring>

#include "selfDB_structs.h"

using namespace std;

void selectAll(Table* table){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    for(int row = 0; row < rowSize; ++row){
        for(int col = 0; col < colSize; ++col){
            cout << table->rowTable[row].columns[col];
            if(col) cout << "|";
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
                cout << table->rowTable[row].columns[col];
                if(col) cout << "|";
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
                cout << table->rowTable[row].columns[col];
                if(col) cout << "|";
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
                cout << table->rowTable[row].columns[col];
                if(col) cout << "|";
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
                cout << table->rowTable[row].columns[col];
                if(col) cout << "|";
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

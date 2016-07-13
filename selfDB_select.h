#include <iostream>
#include <cstring>
#include <vector>

#include "selfDB_structs.h"

using namespace std;

void printColumn(Table* table, int row, int col){
    if(col) cout << "|";

    if(!strcmp(table->tableSchema[col].type, "int")){
        cout << *(uint32_t*)(table->rowTable[row].columns[col]);
    }
    else if(!strcmp(table->tableSchema[col].type, "bigint")){
        cout << *(uint64_t*)(table->rowTable[row].columns[col]);
    }
    else if(!strcmp(table->tableSchema[col].type, "char")){
        cout << *(char*)(table->rowTable[row].columns[col]);
    }
    else if(!strcmp(table->tableSchema[col].type, "decimal")){
        cout << *(float*)(table->rowTable[row].columns[col]);
    }
    else if(!strcmp(table->tableSchema[col].type, "double")){
        cout << *(double*)(table->rowTable[row].columns[col]);
    }
}

void selectAll(vector<string> query, Table* table){
    int count = 0;
    int colSize = table->colSize;
    int rowSize = table->rowSize;

    if(!strcmp(query.at(1).c_str(),"all")){
        for(int i = 0; i < table->colSize; ++i){
            if(i)    cout << "|";
            cout << table->tableSchema[i].name;
        }
        cout << endl;
        for(int row = 0; row < rowSize; ++row){
            for(int colIterator = 0; colIterator < table->colSize; ++colIterator){
                printColumn(table, row, colIterator);
            }
            cout << endl;
            ++count;
        }
    }
    else{
        int fromCount = 0;
        for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
            if(!strcmp((*it).c_str(), "from"))  break;
            ++fromCount;
        }

        int* colList = new int[fromCount - 1];

        bool isFirst = 1;
        int colListIndex = 0;
        for(int i = 0; i < table->colSize; ++i){
            for(int j = 1; j < fromCount; ++j){
                if(!strcmp(query.at(j).c_str(), table->tableSchema[i].name)){
                    if(!isFirst)    cout << "|";
                    else            isFirst = 0;
                    cout << table->tableSchema[i].name;
                    colList[colListIndex] = i;
                    ++colListIndex;
                }
            }
        }
        if(colListIndex == 0){
            cout << "No such column" << endl;
            return;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            int col = 0;
            for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                col = colList[colIterator];
                printColumn(table, row, col);
            }
            cout << endl;
            ++count;
        }
    }
    cout << count << " row(s) selected" << endl;
}

void selectGreater(vector<string> query, Table* table, const char* colName, const char*  operand){
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
        return;
    }

    int flag = -1;
    if(!strcmp(table->tableSchema[selectedCol].type, "int")){
        flag = 0;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "bigint")){
        flag = 1;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "char")){
        flag = 2;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "decimal")){
        flag = 3;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "double")){
        flag = 4;
    }

    if(!strcmp(query.at(1).c_str(),"all")){
        for(int i = 0; i < table->colSize; ++i){
            if(i)   cout << "|";
            cout << table->tableSchema[i].name;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) > (uint32_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) > (uint64_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand)>0){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) > atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) > atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
        }
    }
    else{
        int fromCount = 0;
        for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
            if(!strcmp((*it).c_str(), "from"))  break;
            ++fromCount;
        }

        int* colList = new int[fromCount - 1];

        bool isFirst = 1;
        int colListIndex = 0;
        for(int i = 0; i < table->colSize; ++i){
            for(int j = 1; j < fromCount; ++j){
                if(!strcmp(query.at(j).c_str(), table->tableSchema[i].name)){
                    if(!isFirst)    cout << "|";
                    else            isFirst = 0;
                    cout << table->tableSchema[i].name;
                    colList[colListIndex] = i;
                    ++colListIndex;
                }
            }
        }
        if(colListIndex == 0){
            cout << "No such column" << endl;
            return;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) > (uint32_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) > (uint64_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand)>0){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) > atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) > atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
        }
    }
    cout << count << " row(s) selected" << endl;
}

void selectGreaterEqual(vector<string> query, Table* table, const char* colName, const char*  operand){
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
        return;
    }

    int flag = -1;
    if(!strcmp(table->tableSchema[selectedCol].type, "int")){
        flag = 0;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "bigint")){
        flag = 1;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "char")){
        flag = 2;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "decimal")){
        flag = 3;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "double")){
        flag = 4;
    }

    if(!strcmp(query.at(1).c_str(),"all")){
        for(int i = 0; i < table->colSize; ++i){
            if(i)   cout << "|";
            cout << table->tableSchema[i].name;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) >= (uint32_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) >= (uint64_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) >= 0){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) >= atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) >= atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
        }
    }
    else{
        int fromCount = 0;
        for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
            if(!strcmp((*it).c_str(), "from"))  break;
            ++fromCount;
        }

        int* colList = new int[fromCount - 1];

        bool isFirst = 1;
        int colListIndex = 0;
        for(int i = 0; i < table->colSize; ++i){
            for(int j = 1; j < fromCount; ++j){
                if(!strcmp(query.at(j).c_str(), table->tableSchema[i].name)){
                    if(!isFirst)    cout << "|";
                    else            isFirst = 0;
                    cout << table->tableSchema[i].name;
                    colList[colListIndex] = i;
                    ++colListIndex;
                }
            }
        }
        if(colListIndex == 0){
            cout << "No such column" << endl;
            return;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) >= (uint32_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) >= (uint64_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) >= 0){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) >= atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) >= atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
        }
    }
    cout << count << " row(s) selected" << endl;
}

void selectLess(vector<string> query, Table* table, const char* colName, const char*  operand){
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
        return;
    }

    int flag = -1;
    if(!strcmp(table->tableSchema[selectedCol].type, "int")){
        flag = 0;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "bigint")){
        flag = 1;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "char")){
        flag = 2;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "decimal")){
        flag = 3;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "double")){
        flag = 4;
    }

    if(!strcmp(query.at(1).c_str(),"all")){
        for(int i = 0; i < table->colSize; ++i){
            if(i)   cout << "|";
            cout << table->tableSchema[i].name;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) < (uint32_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) < (uint64_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) < 0){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) < atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) < atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
        }
    }
    else{
        int fromCount = 0;
        for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
            if(!strcmp((*it).c_str(), "from"))  break;
            ++fromCount;
        }

        int* colList = new int[fromCount - 1];

        bool isFirst = 1;
        int colListIndex = 0;
        for(int i = 0; i < table->colSize; ++i){
            for(int j = 1; j < fromCount; ++j){
                if(!strcmp(query.at(j).c_str(), table->tableSchema[i].name)){
                    if(!isFirst)    cout << "|";
                    else            isFirst = 0;
                    cout << table->tableSchema[i].name;
                    colList[colListIndex] = i;
                    ++colListIndex;
                }
            }
        }
        if(colListIndex == 0){
            cout << "No such column" << endl;
            return;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) < (uint32_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) < (uint64_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) < 0){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) < atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) < atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
        }
    }
    cout << count << " row(s) selected" << endl;
}

void selectLessEqual(vector<string> query, Table* table, const char* colName, const char*  operand){
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
        return;
    }

    int flag = -1;
    if(!strcmp(table->tableSchema[selectedCol].type, "int")){
        flag = 0;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "bigint")){
        flag = 1;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "char")){
        flag = 2;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "decimal")){
        flag = 3;
    }
    else if(!strcmp(table->tableSchema[selectedCol].type, "double")){
        flag = 4;
    }

    if(!strcmp(query.at(1).c_str(),"all")){
        for(int i = 0; i < table->colSize; ++i){
            if(i)   cout << "|";
            cout << table->tableSchema[i].name;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) <= (uint32_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) <= (uint64_t)atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) <= 0){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) <= atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) <= atoi(operand)){
                    for(int col = 0; col < colSize; ++col){
                        printColumn(table, row, col);
                    }
                    ++count;
                    cout << endl;
                }
            }
        }
    }
    else{
        int fromCount = 0;
        for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
            if(!strcmp((*it).c_str(), "from"))  break;
            ++fromCount;
        }

        int* colList = new int[fromCount - 1];

        bool isFirst = 1;
        int colListIndex = 0;
        for(int i = 0; i < table->colSize; ++i){
            for(int j = 1; j < fromCount; ++j){
                if(!strcmp(query.at(j).c_str(), table->tableSchema[i].name)){
                    if(!isFirst)    cout << "|";
                    else            isFirst = 0;
                    cout << table->tableSchema[i].name;
                    colList[colListIndex] = i;
                    ++colListIndex;
                }
            }
        }
        if(colListIndex == 0){
            cout << "No such column" << endl;
            return;
        }
        cout << endl;

        for(int row = 0; row < rowSize; ++row){
            if(flag == 0){
                if(*(uint32_t*)(table->rowTable[row].columns[selectedCol]) <= (uint32_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 1){
                if(*(uint64_t*)(table->rowTable[row].columns[selectedCol]) <= (uint64_t)atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 2){
                if(strcmp((const char*)(table->rowTable[row].columns[selectedCol]),  operand) <= 0){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 3){
                if(*(float*)(table->rowTable[row].columns[selectedCol]) <= atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
            else if(flag == 4){
                if(*(double*)(table->rowTable[row].columns[selectedCol]) <= atoi(operand)){
                    int col = 0;
                    for(int colIterator = 0; colIterator < fromCount-1; ++colIterator){
                        col = colList[colIterator];
                        printColumn(table, row, col);
                    }
                    cout << endl;
                    ++count;
                }
            }
        }
    }
    cout << count << " row(s) selected" << endl;
}

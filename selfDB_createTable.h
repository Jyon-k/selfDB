#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "selfDB_structs.h"

using namespace std;

Schema* createSchema(vector<string> query){

    int countColumn = 0;

    Schema* newSchema = new Schema[(query.size()-3)/2];

    for(int i = 3; i < query.size(); ++i){
        if(i%2){
            if(!strcmp(query.at(i).c_str(), "int")){
                newSchema[i-3].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[i-3].name, query.at(i+1).c_str());
                newSchema[i-3].type = new char[4];
                strcpy(newSchema[i-3].type, "int");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "bigint")){
                newSchema[i-3].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[i-3].name, query.at(i+1).c_str());
                newSchema[i-3].type = new char[7];
                strcpy(newSchema[i-3].type, "bigint");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "char")){
                newSchema[i-3].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[i-3].name, query.at(i+1).c_str());
                newSchema[i-3].type = new char[5];
                strcpy(newSchema[i-3].type, "char");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "decimal")){
                newSchema[i-3].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[i-3].name, query.at(i+1).c_str());
                newSchema[i-3].type = new char[8];
                strcpy(newSchema[i-3].type, "decimal");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "double")){
                newSchema[i-3].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[i-3].name, query.at(i+1).c_str());
                newSchema[i-3].type = new char[7];
                strcpy(newSchema[i-3].type, "double");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else{
                cout << "Wrong type error!" << endl;
                return NULL;
            }
        }
    }
    return newSchema;
}

Table* createTable(vector<string> query, const char* tableName){

    Table* newRowTable = new Table;

    newRowTable->tableName = new char[strlen(tableName) + 1];
    strcpy(newRowTable->tableName, tableName);
    newRowTable->tableSchema = createSchema(query);
    newRowTable->colSize = (query.size()-3)/2;
}


/*
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
*/

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
                newSchema[(i-3)/2].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[(i-3)/2].name, query.at(i+1).c_str());
                newSchema[(i-3)/2].type = new char[4];
                strcpy(newSchema[(i-3)/2].type, "int");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "bigint")){
                newSchema[(i-3)/2].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[(i-3)/2].name, query.at(i+1).c_str());
                newSchema[(i-3)/2].type = new char[7];
                strcpy(newSchema[(i-3)/2].type, "bigint");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "char")){
                newSchema[(i-3)/2].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[(i-3)/2].name, query.at(i+1).c_str());
                newSchema[(i-3)/2].type = new char[5];
                strcpy(newSchema[(i-3)/2].type, "char");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "decimal")){
                newSchema[(i-3)/2].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[(i-3)/2].name, query.at(i+1).c_str());
                newSchema[(i-3)/2].type = new char[8];
                strcpy(newSchema[(i-3)/2].type, "decimal");
                //newSchema[i-3].columnNumber = countColumn++;
            }
            else if(!strcmp(query.at(i).c_str(), "double")){
                newSchema[(i-3)/2].name = new char[strlen(query.at(i+1).c_str()) + 1];
                strcpy(newSchema[(i-3)/2].name, query.at(i+1).c_str());
                newSchema[(i-3)/2].type = new char[7];
                strcpy(newSchema[(i-3)/2].type, "double");
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
    if(newRowTable-> tableSchema == NULL){
        return NULL;
    }
    newRowTable->colSize = (query.size()-3)/2;


    cout << "Create new table!" << endl;
    for(int col = 0; col < newRowTable->colSize; ++col){
        if(!col) cout << "-";
        for(int i = 0; i < strlen(newRowTable->tableSchema[col].name)+3; ++i){
            cout << "-";
        }
    }
    cout << endl;

    cout << "| ";
    for(int col = 0; col < newRowTable->colSize; ++col){
        if(col) cout << " | ";
        cout << newRowTable->tableSchema[col].name;
    }
    cout << " |";
    cout << endl;

    for(int col = 0; col < newRowTable->colSize; ++col){
        if(!col) cout << "-";
        for(int i = 0; i < strlen(newRowTable->tableSchema[col].name)+3; ++i){
            cout << "-";
        }
    }
    cout << endl;

    return newRowTable;
}



#include <iostream>
#include <cstring>
#include <vector>

#include "selfDB_structs.h"

using namespace std;

void showDatabases(vector<string> query){
}

void showTables(vector<string> query, vector<Table*> database){
    for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
        cout << (*it)->tableName << endl;
    }
}

void showSchema(vector<string> query, Table* selectedTable){
    for(int col = 0; col < selectedTable->colSize; ++col){
        if(!col) cout << "-";
        for(int i = 0; i < strlen(selectedTable->tableSchema[col].name)+3; ++i){
            cout << "-";
        }
    }
    cout << endl;

    cout << "| ";
    for(int col = 0; col < selectedTable->colSize; ++col){
        if(col) cout << " | ";
        cout << selectedTable->tableSchema[col].name;
    }
    cout << " |";
    cout << endl;

    for(int col = 0; col < selectedTable->colSize; ++col){
        if(!col) cout << "-";
        for(int i = 0; i < strlen(selectedTable->tableSchema[col].name)+3; ++i){
            cout << "-";
        }
    }
    cout << endl;
}

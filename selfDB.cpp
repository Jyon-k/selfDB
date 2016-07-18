#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

#include "selfDB_structs.h"
#include "selfDB_query.h"
#include "selfDB_createTable.h"
#include "selfDB_load.h"
#include "selfDB_show.h"
#include "selfDB_select.h"

using namespace std;

#define CREATE  "create"
#define LOAD    "load"
#define SHOW    "show"
#define SELECT  "select"
#define INSERT  "insert"
#define QUIT    "quit"
#define EXIT    "exit"

int main(int argc, char* argv[]){

    cout << "******************************" << endl;
    cout << "************selfDB************" << endl;
    cout << "******************************" << endl;

    vector<Table*> database;

    while(1){
        string cmd_tmp;
        cout << ">> ";
        getline(cin, cmd_tmp);
        if(cmd_tmp.empty()){
            cout << endl;
            continue;
        }
        vector<string> query = split(cmd_tmp);
        const char* command = query.at(0).c_str();

        if(!strcmp(command, CREATE)){
            const char* type = query.at(1).c_str();
            if(!strcmp(type, "database")){
            }
            else if(!strcmp(type, "table")){
                const char* tableName = query.at(2).c_str();

                Table* newTable = createTable(query, tableName);
                if(newTable != NULL)    database.push_back(newTable);
                else                    continue;
            }
            else{
                cout << "Wrong command!!" << endl;
                continue;
            }
        }
        else if(!strcmp(command, LOAD)){
            const char* tableName = query.at(1).c_str();
            const char* with = query.at(2).c_str();
            const char* CSV = query.at(3).c_str();

            if(strcmp(with, "with")){
                cout << "Wrong command!!" << endl;
                continue;
            }

            ifstream ifs;
            ifs.open(CSV);

            int lc = count(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>(), '\n');
            ifs.close();
            ifs.open(CSV);

            if(!ifs){
                cout << "Input file is empty!" << endl;
                continue;
            }
            else{
                Table* selectedTable;
                for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                    if(!strcmp((*it)->tableName, tableName)){
                        selectedTable = (*it);
                        break;
                    }
                }
                loadCSVwithSegment(ifs, selectedTable, lc);
            }
        }
        else if(!strcmp(command, SHOW)){
            if(!strcmp(query.at(1).c_str(), "databases")){
                showDatabases(query);
            }
            else if(!strcmp(query.at(1).c_str(), "tables")){
                showTables(query, database);
            }
            else if(!strcmp(query.at(1).c_str(), "schema")){
                if(query.size() < 3){
                    cout << "Wrong command!!" << endl;
                    continue;
                }

                const char* tableName = query.at(2).c_str();
                Table* selectedTable;
                for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                    if(!strcmp((*it)->tableName, tableName)){
                        selectedTable = (*it);
                        break;
                    }
                }
                showSchema(query, selectedTable);
            }
            else{
                cout << "Wrong command!!" << endl;
                continue;
            }
        }
        else if(!strcmp(command, SELECT)){
            if(database.empty()){
                cout << "No table exists!!" << endl;
                continue;
            }
            if(query.size() < 4){
                cout << "Wrong command!!" << endl;
                continue;
            }

            int fromCount = 0;
            for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
                if(!strcmp((*it).c_str(), "from"))  break;
                ++fromCount;
            }
            bool isWhere = 0;
            int whereCount = 0;
            for(vector<string>::iterator it = query.begin(); it != query.end(); ++it){
                if(!strcmp((*it).c_str(), "where")){
                    isWhere = 1;
                    break;
                }
                ++whereCount;
            }

            const char* tableName = query.at(fromCount + 1).c_str();

            Table* selectedTable;
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                if(!strcmp((*it)->tableName, tableName)){
                    selectedTable = (*it);
                    break;
                }
            }

            if(!isWhere){
                selectAll(query, selectedTable);
            }
            else{
                if(query.size() < whereCount + 4){
                    cout << query.size() << endl;
                    cout << "Wrong command!!" << endl;
                    continue;
                }

                const char* selectedColumn = query.at(whereCount + 1).c_str();
                const char* selectOperator = query.at(whereCount + 2).c_str();
                const char* selectOperand = query.at(whereCount + 3).c_str();
                if(!strcmp(selectOperator, ">")){
                    selectGreater(query, selectedTable, selectedColumn, selectOperand);
                }
                else if(!strcmp(selectOperator, ">=")){
                    selectGreaterEqual(query, selectedTable, selectedColumn, selectOperand);
                }
                else if(!strcmp(selectOperator, "<")){
                    selectLess(query, selectedTable, selectedColumn, selectOperand);
                }
                else if(!strcmp(selectOperator, "<=")){
                    selectLessEqual(query, selectedTable, selectedColumn, selectOperand);
                }
                else{
                    cout << "Wrong Operator!!" << endl;
                    continue;
                }
            }
        }
        else if(!strcmp(command, INSERT)){
        }
        else if(!strcmp(command, QUIT)||!strcmp(command, EXIT)){
            cout << "******************************" << endl;
            cout << "*********quit selfDB**********" << endl;
            cout << "******************************" << endl;
            return 0;
        }
        else{
            cout << "WRONG COMMAND!!" << endl;
            continue;
        }
    }

    return 0;
}

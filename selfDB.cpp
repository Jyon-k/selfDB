#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

#include "selfDB_structs.h"
#include "selfDB_createTable.h"
#include "selfDB_select.h"
#include "selfDB_query.h"
#include "selfDB_load.h"

using namespace std;

#define CREATE  "create"
#define LOAD    "load"
#define LIST    "list"
#define SELECT  "select"
#define QUIT    "quit"

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
        vector<string> commandSet = split(cmd_tmp);
        const char* command = commandSet.at(0).c_str();

        if(!strcmp(command, CREATE)){
            const char* type = commandSet.at(1).c_str();
            if(!strcmp(type, "database")){
            }
            else if(!strcmp(type, "table")){
                //string tbl_tmp;
                //string TBN_tmp;
                //cout << "CSV file : ";
                //cin >> tbl_tmp;
                //cout << "Table name : ";
                //cin >> TBN_tmp;

                const char* tableName = commandSet.at(2).c_str();

                //ifstream ifs;
                //ifs.open(table);

                //int lc = count(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>(), '\n');
                //ifs.close();
                //ifs.open(table);

                //if(!ifs){
                //    cout << "Input file is empty!" << endl;
                //}
                //else{
                    //database.push_back(create(ifs, tableName, lc));
                //}

                Table* newTable = createTable(commandSet, tableName);
                for(int col = 0; col < newTable->colSize; ++col){
                    cout << newTable->tableSchema[col].name << endl;
                }
                if(newTable != NULL){
                    database.push_back(newTable);
                }
            }
        }
        else if(!strcmp(command, LOAD)){
            const char* tableName = commandSet.at(1).c_str();
            const char* with = commandSet.at(2).c_str();
            const char* CSV = commandSet.at(3).c_str();

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
            }
            else{
                Table* selectedTable;
                for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                    if(!strcmp((*it)->tableName, tableName)){
                        selectedTable = (*it);
                        break;
                    }
                }
                loadCSV(ifs, selectedTable, lc);
            }
        }
        else if(!strcmp(command, LIST)){
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                cout << (*it)->tableName << endl;
            }
        }
        else if(!strcmp(command, SELECT)){
            if(database.empty()){
                cout << "No table exists!!" << endl;
                continue;
            }
            if(commandSet.size() < 4 || strcmp(commandSet.at(2).c_str(), "from")){
                cout << "Wrong command!!" << endl;
                continue;
            }

            const char* column = commandSet.at(1).c_str();
            const char* tableName = commandSet.at(3).c_str();

            Table* selectedTable;
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                if(!strcmp((*it)->tableName, tableName)){
                    selectedTable = (*it);
                    break;
                }
            }
            /*
            Row* rowTable;
            int lc;
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
               if(strcmp(tableName, (*it)->tableName) == 0){
                    rowTable = (*it)->rowTable;
                   lc = (*it)->rowSize;
                }
            }
            */


            if(!strcmp(column, "all") || !strcmp(column, "*")){
                if(commandSet.size() == 4){
                    selectAll(selectedTable);

                    //selectAll(rowTable, lc);
                }
                else{
                    if(commandSet.size() < 8 || strcmp(commandSet.at(4).c_str(), "where")){
                        cout << "Wrong command!!" << endl;
                        continue;
                    }

                    const char* selectedColumn = commandSet.at(5).c_str();
                    const char* selectOperand = commandSet.at(7).c_str();
                    const char* selectOperator = commandSet.at(6).c_str();
                    if(!strcmp(selectOperator, ">")){
                        selectGreater(selectedTable, selectedColumn, selectOperand);
                    }
                    else if(!strcmp(selectOperator, ">=")){
                        selectGreaterEqual(selectedTable, selectedColumn, selectOperand);
                    }
                    else if(!strcmp(selectOperator, "<")){
                        selectLess(selectedTable, selectedColumn, selectOperand);
                    }
                    else if(!strcmp(selectOperator, "<=")){
                        selectLessEqual(selectedTable, selectedColumn, selectOperand);
                    }
                    else{
                        cout << "Wrong Operator!!" << endl;
                    }


                    /*
                    if(!strcmp(selectedColumn, "orderKey")){
                        cout << "Sorry, not yet provided..." << endl;

                    }
                    else if(!strcmp(selectedColumn, "custKey")){
                        cout << "Sorry, not yet provided..." << endl;
                    }
                    else if(!strcmp(selectedColumn, "totalPrice")){
                        double selectOperand = stod(commandSet.at(7));
                        const char* selectOperator = commandSet.at(6).c_str();
                        if(!strcmp(selectOperator, ">")){
                            selectGreater(rowTable, lc, selectOperand);
                        }
                        else if(!strcmp(selectOperator, ">=")){
                            selectGreaterEqual(rowTable, lc, selectOperand);
                        }
                        else if(!strcmp(selectOperator, "<")){
                            selectLess(rowTable, lc, selectOperand);
                        }
                        else if(!strcmp(selectOperator, "<=")){
                            selectLessEqual(rowTable, lc, selectOperand);
                        }
                        else{
                            cout << "Wrong Operator!!" << endl;
                        }
                    }
                    else{
                        cout << "There is no such comlumn!!" << endl;
                    }
                    */
                }
            }
            else if(!strcmp(column, "orderKey")){
                cout << "Sorry, not yet provided..." << endl;
            }
            else if(!strcmp(column, "custKey")){
                cout << "Sorry, not yet provided..." << endl;
            }
            else if(!strcmp(column, "totalPrice")){
                cout << "Sorry, not yet provided..." << endl;
            }
            else{
                cout << "There is no such comlumn!!" << endl;
            }
            /*
            string TBN_tmp;
            cout << "Table Name : ";
            cin >> TBN_tmp;
            const char* tableName = TBN_tmp.c_str();

            bool flag = 0;
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                if(strcmp(tableName, (*it)->tableName) == 0){
                    flag = 1;
                }
            }

            if(!flag){
                cout << "No such table!!" << endl;
                continue;
            }

            Row* rowTable;
            int lc;
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
               if(strcmp(tableName, (*it)->tableName) == 0){
                    rowTable = (*it)->rowTable;
                   lc = (*it)->rowSize;
                }
            }

            string sop_tmp;
            coiut << "Operator : ";
            cin >> sop_tmp;
            const char* selectOperator = sop_tmp.c_str();

            if(strcmp(selectOperator, "all") == 0){
                selectAll(rowTable, lc);
            }
            else{
                double selectOperand;
                cout << "Double value : ";
                cin >> selectOperand;
                if(!strcmp(selectOperator, ">")){
                    selectGreater(rowTable, lc, selectOperand);
                }
                else if(!strcmp(selectOperator, ">=")){
                    selectGreaterEqual(rowTable, lc, selectOperand);
                }
                else if(!strcmp(selectOperator, "<")){
                    selectLess(rowTable, lc, selectOperand);
                }
                else if(!strcmp(selectOperator, "<=")){
                    selectLessEqual(rowTable, lc, selectOperand);
                }
                else{
                    cout << "Wrong Operator!!" << endl;
                }
            }
            */
        }
        else if(!strcmp(command, QUIT)){
            cout << "******************************" << endl;
            cout << "*********quit selfDB**********" << endl;
            cout << "******************************" << endl;
            return 0;
        }
        else{
            cout << "WRONG COMMAND!!" << endl;
        }
    }

    return 0;
}

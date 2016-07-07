#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

#include "selfDB_structs.h"
#include "selfDB_createTable.h"
#include "selfDB_select.h"

using namespace std;

#define CREATE  "create"
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
        cin >> cmd_tmp;
        const char* command = cmd_tmp.c_str();

        if(strcmp(command, CREATE) == 0){
            string tbl_tmp;
            string TBN_tmp;
            cout << "CSV file : ";
            cin >> tbl_tmp;
            cout << "Table name : ";
            cin >> TBN_tmp;

            const char* table = tbl_tmp.c_str();
            const char* tableName = TBN_tmp.c_str();

            ifstream ifs;
            ifs.open(table);

            int lc = count(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>(), '\n');
            ifs.close();
            ifs.open(table);

            if(!ifs){
                cout << "Input file is empty!" << endl;
            }
            else{
                database.push_back(create(ifs, tableName, lc));
            }
        }
        else if(strcmp(command, LIST) == 0){
            for(vector<Table*>::iterator it = database.begin(); it != database.end(); ++it){
                cout << (*it)->tableName << endl;
            }
        }
        else if(strcmp(command, SELECT) == 0){
            if(database.empty()){
                cout << "No table exists!" << endl;
                continue;
            }
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
            cout << "Operator : ";
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
        }
        else if(strcmp(command, QUIT) == 0){
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

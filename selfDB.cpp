#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <algorithm>

#include "selfDB_row.h"
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


    map<const char*, Row*> database;
    map<const char*, int> lineCount;

    while(1){
        string cmd_tmp;
        cout << ">> ";
        cin >> cmd_tmp;
        const char* command = cmd_tmp.c_str();

        if(!strcmp(command, CREATE)){
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
                database[tableName] = create(ifs, lc);
                lineCount[tableName] = lc;
            }
        }
        else if(!strcmp(command, LIST)){
            for(auto& x: database){
                cout << x.first << endl;
            }
        }
        else if(!strcmp(command, SELECT)){
            if(database.empty()){
                cout << "No table exists!" << endl;
                continue;
            }
            string TBN_tmp;
            cout << "Table Name : ";
            cin >> TBN_tmp;
            const char* tableName = TBN_tmp.c_str();

            Row* rowTable = database[tableName];
            int lc = lineCount[tableName];

            string sop_tmp;
            cout << "Operator : ";
            cin >> sop_tmp;
            const char* selectOperator = sop_tmp.c_str();

            if(!strcmp(selectOperator, "all")){
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
        else if(!strcmp(command, QUIT)){
            cout << "******************************" << endl;
            cout << "*********quit selfDB**********" << endl;
            cout << "******************************" << endl;
            break;
        }
        else{
            cout << "WRONG COMMAND!!" << endl;
        }
    }

    return 0;
}

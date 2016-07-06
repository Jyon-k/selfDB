#include <iostream>
#include <fstream>
#include "selfDB_row.h"

using namespace std;

Row* create(ifstream &ifs, int lineCount){

    cout << "Create Table" << endl;

    //actually read the line
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

    return newTable;
}

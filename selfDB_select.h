#include <iostream>

#include "selfDB_structs.h"

using namespace std;

void selectAll(Row* rowTable, int lineCount){
    int count = 0;
    cout << "order key|cust key|total price"<<endl;
    for(int row = 0; row < lineCount; ++row){
        cout << rowTable[row].orderKey << "|"
            << rowTable[row].custKey << "|"
            << rowTable[row].totalPrice << endl;
        ++count;
    }
    cout << count << " row(s) selected" << endl;
}

void selectGreater(Row* rowTable, int lineCount, double operand){
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
}

void selectGreaterEqual(Row* rowTable, int lineCount, double operand){
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
}

void selectLess(Row* rowTable, int lineCount, double operand){
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
}

void selectLessEqual(Row* rowTable, int lineCount, double operand){
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
}

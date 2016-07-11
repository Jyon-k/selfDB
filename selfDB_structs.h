#ifndef _ROW_H_
#define _ROW_H_

#include <iostream>
#include <cstdint>

using namespace std;

struct Row{
    //uint32_t orderKey;
    //uint32_t custKey;
    //double totalPrice;
    void** columns;
};

struct Schema{
    char* name;
    char* type;
    //int columnNumber;
};

struct Table{
    char* tableName;
    Row* rowTable;
    Schema* tableSchema;
    int colSize;
    int rowSize;
};

/*
class Database{
    private:
        char* DBName;
        Table* tableSet;
        Database* nextDB;
    public:
        Database();
        Database(char* DBName);
        ~Database();
        void setDBName();
        bool find();
        Row* getTable();
        void createTable();
};

class DatabaseSet{
    private:
        Database* DBset;
    public:
        DatabaseSet();
        ~DatabaseSet();
        void insert();
        bool find();
        Database* getDB();
};
*/
#endif

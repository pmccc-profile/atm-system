#ifndef ATMSQL_H
#define ATMSQL_H

#include "sqlite3.h"
#include <string>

using namespace std;


class ATMsql
{
    public:
        //immediately initialize variable/s
        ATMsql();
        //destroy database connection
        ~ATMsql();
        //create database connection
        bool createConnection();
        //create table/s
        bool createTable();
        //drop table/s
        bool dropTable();
        //executed automatically when called in sqlite3_exec() | will only execute if a matching record found
        //*data = your variable (target), argc = column count, **argv = table records/values, **colNames = column names
        static int printRecord(void *data, int argc, char **argv, char **colNames);
        //CRUD ********
        bool createRecord();
        bool readRecord(string sqlRead);
        bool updateRecord(string sqlUpdate);
        bool deleteValue(string sqlDelete);
        //END *********

    private:
        sqlite3 *dbcon; //database connection
        const char *dbName; //database name in characters (sqlite3 uses C, hence, only characters)
        const char *sql; //database query in characters (sqlite3 uses C, hence, only characters)
        char *errMsg = nullptr; //database error message
};

#endif // ATMSQL_H

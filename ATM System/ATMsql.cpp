#include "ATMsql.h"

#include <iostream>
#include <string>

using namespace std;


//using (:) member initializer to initialize parameters directly on constructor
ATMsql::ATMsql() : dbName("dbATM.db"), dbcon(nullptr)
{
    //automatically call/trigger the functions
    createConnection();
    createTable();
    createRecord();
}

ATMsql::~ATMsql(){
    //NOTE: sqlite3 pointer, hence, *db returns non-zero value if TRUE (contains memory address)

    //check if db is TRUE
    if(dbcon){
        //to start anew
        dropTable();
        //close connection
        sqlite3_close(dbcon);
    }
}

bool ATMsql::createConnection(){
    //NOTE: sqlite3_open() returns 0 if connection successful

    //check if returned a non-zero value, hence, connection fails
    if(sqlite3_open(dbName,&dbcon)){
        cerr<<"Connection unsuccessful. "<<errMsg<<endl;
        return false;
    }
    return true;
}
bool ATMsql::createTable(){
    //automatically create table if non-existent
    sql = "CREATE TABLE IF NOT EXISTS Account("
    "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "AccountNumber BIGINT UNIQUE,"
    "AccountBalance INTEGER,"
    "ExpirationDate DATE,"
    "Pin INTEGER);";

    if(sqlite3_exec(dbcon,sql,nullptr,nullptr,&errMsg)==SQLITE_OK){
        //create table successful
        return true;
    }else{
        cerr<<"Table error: "<<errMsg<<endl;
        //free errMsg memory
        sqlite3_free(errMsg);
    }
    //create table unsuccessful
    return false;
}
bool ATMsql::dropTable(){
    //automatically create table if non-existent
    sql = "DROP TABLE IF EXISTS Account;;";

    if(sqlite3_exec(dbcon,sql,nullptr,nullptr,&errMsg)==SQLITE_OK){
        //create table successful
        return true;
    }else{
        cerr<<"Table error: "<<errMsg<<endl;
        //free errMsg memory
        sqlite3_free(errMsg);
    }
    //create table unsuccessful
    return false;
}

//executed automatically when called in sqlite3_exec() | will only execute if a matching record found
int ATMsql::printRecord(void *data, int argc, char **argv, char **colNames){
    //cast into original source data type and reference: "int found=0"
    int *dFound = static_cast<int*>(data);
    *dFound = 1; //record found

    cout<<"*******************************************************"<<endl;
    //temporarily print everything for checking purposes
    for (int i=0; i<argc; i++){
        //print per row: column, value (if null, print NULL)
        cout<<colNames[i]<<": "<<(argv[i] ? argv[i] : "NULL")<<endl;
    }
    cout<<"*******************************************************"<<endl;

    //success like int main() return 0;
    return 0;
}

//CRUD *******************

bool ATMsql::createRecord(){
    //IGNORE to avoid duplication
    sql = "INSERT OR IGNORE INTO Account(AccountNumber,AccountBalance,ExpirationDate,Pin) VALUES"
          "(8291234567, 500000, '2026-09-14', 1234),"
          "(8298910111, 10000, '2027-09-14', 2345),"
          "(8299101112, 3515, '2025-07-30', 3456),"
          "(8299101113, 22350, '2026-02-08', 4567),"
          "(8299101114, 1875, '2025-01-16', 5678);";

    if(sqlite3_exec(dbcon,sql,nullptr,nullptr,&errMsg)==SQLITE_OK){
        return true;
    }else{
        cerr<<"INSERT error. "<<errMsg<<endl;
        sqlite3_free(errMsg);
    }
    return false;
}

bool ATMsql::readRecord(string sqlRead){

    int dataFound = 0;

    //&datafound is the void *data argument for printRecord()
    if(sqlite3_exec(dbcon,sqlRead.c_str(),&printRecord,&dataFound,&errMsg)==SQLITE_OK){
        return dataFound > 0;
    }else{
        cerr<<"READ error. "<<errMsg<<endl;
        sqlite3_free(errMsg);
    }
    return false;
}

bool ATMsql::updateRecord(string sqlUpdate){
    if(sqlite3_exec(dbcon,sqlUpdate.c_str(),nullptr,nullptr,&errMsg)==SQLITE_OK){
        return true;
    }else{
        cerr<<"UPDATE error. "<<errMsg<<endl;
        sqlite3_free(errMsg);
    }
    return false;
}

bool ATMsql::deleteValue(string sqlDelete){
    if(sqlite3_exec(dbcon,sqlDelete.c_str(),nullptr,nullptr,&errMsg)==SQLITE_OK){
        return true;
    }else{
        cerr<<"DELETE error. "<<errMsg<<endl;
        sqlite3_free(errMsg);
    }
    return false;
}

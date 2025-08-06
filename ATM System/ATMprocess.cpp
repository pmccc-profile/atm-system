#include "ATMprocess.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>  // for std::put_time

using namespace std;

ATMprocess::ATMprocess() : withdrawAmount(0)
{
    //ctor
}

/*
ATMprocess::~ATMprocess()
{
    //dtor
}
*/

bool ATMprocess::balanceCheck(long long cardAcct){

    stringstream ss;
    ss<<"SELECT AccountBalance FROM Account WHERE AccountNumber = "<<cardAcct<<";";

    return readRecord(ss.str());
}

bool ATMprocess::printReceipt(long long cardNumber){

    //get time now
    time_t now = time(0);

    //covert to tm struct
    tm *ltm = localtime(&now);

    //format into YYYY-MM-DD
    cout<<"Date: "
        <<put_time(ltm, "%Y-%m-%d %H:%M:%S")<<endl;

    stringstream ss;
    ss<<"SELECT AccountNumber, AccountBalance FROM Account WHERE AccountNumber = "<<cardNumber<<";";


    return readRecord(ss.str());

}

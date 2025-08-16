#include "ATMprocess.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>  // for std::put_time

using namespace std;

ATMprocess::ATMprocess() : withdrawAmount(0), depositAmount(0)
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

void ATMprocess::setWithdrawalAmt(int withdrawAmt){
    withdrawAmount = withdrawAmt;
}

int ATMprocess::getWithdrawalAmt(){
    return withdrawAmount;
}

void ATMprocess::setDepositAmt(int depositAmt){
    depositAmount = depositAmt;
}

int ATMprocess::getDepositAmt(){
    return depositAmount;
}

bool ATMprocess::updateBalance(char t){

    long long accountNum = getAcctNum();
    stringstream ss;

    if(t=='w'){
        int withdrawAmt = getWithdrawalAmt();
        ss<<"UPDATE Account SET AccountBalance = (AccountBalance - "<<withdrawAmt<<") WHERE AccountNumber = "<<accountNum<<" AND AccountBalance >= "<<withdrawAmt<<";";
    }else if(t=='d'){
        int depositAmt = getDepositAmt();
        ss<<"UPDATE Account SET AccountBalance = (AccountBalance + "<<depositAmt<<") WHERE AccountNumber = "<<accountNum<<";";
    }

    return updateRecord(ss.str());
}

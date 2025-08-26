#include "ATMprocess.h"
#include "CenterScreen.h"

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

    CenterScreen center;

    cout<<endl<<endl;
    center.positionCenter("-------------------------------------------------------");
    cout<<endl;

    stringstream ss;
    ss<<"SELECT AccountBalance FROM Account WHERE AccountNumber = "<<cardAcct<<";";

    return readRecord(ss.str(),1);
}

bool ATMprocess::printReceipt(long long cardNumber, int t){

    CenterScreen center;

    //get time now
    time_t now = time(0);

    //covert to tm struct
    tm *ltm = localtime(&now);

    //format into YYYY-MM-DD
    stringstream dt;
    dt<<"Date: "<<put_time(ltm, "%Y-%m-%d %H:%M:%S");
    center.positionCenter(dt.str());
    cout<<endl<<endl;

    if(t==1){
        center.positionCenter("Transaction: Balance");
        cout<<endl;
    }else if(t==2){
        string wa = "Amount: " + to_string(withdrawAmount);

        center.positionCenter("Transaction: Withdrawal");
        cout<<endl;
        center.positionCenter(wa);
        cout<<endl;
    }else if(t==3){
        string da = "Amount: " + to_string(depositAmount);

        center.positionCenter("Transaction: Deposit");
        cout<<endl;
        center.positionCenter(da);
        cout<<endl;
    }

    stringstream ss;
    ss<<"SELECT AccountNumber, AccountBalance FROM Account WHERE AccountNumber = "<<cardNumber<<";";

    return readRecord(ss.str(),1);
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

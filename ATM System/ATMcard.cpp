#include "ATMcard.h"

#include <iostream>
#include <sstream>

using namespace std;

ATMcard::ATMcard() : acctNum(0), balance(0), expiryDate(""), pin(0)
{
}
/*
ATMcard::~ATMcard()
{
    //dtor
}
*/

//CARD DETAILS **************************
void ATMcard::setAcctNum(long long accNum){
    acctNum = accNum;
}
long long ATMcard::getAcctNum(){
    return acctNum;
}
void ATMcard::setExpDate(string expDate){
    expiryDate = expDate;
}
string ATMcard::getExpDate(){
    return expiryDate;
}
void ATMcard::setAcctPin(int accPin){
    pin = accPin;
}
int ATMcard::getAcctPin(){
    return pin;
}
//END DETAILS ***************************

//VERIFY DETAILS ************************
bool ATMcard::verifyAcctNum(){
    long long accountNum = getAcctNum();
    if (accountNum == 0) return false;

    stringstream ss;
    ss<<"SELECT * FROM Account WHERE AccountNumber="<<accountNum<<";";

    return readRecord(ss.str());
}
bool ATMcard::verifyExpDate(){
    long long accountNum = getAcctNum();
    if (accountNum == 0) return false;

    stringstream ss;
    ss<<"SELECT ExpirationDate FROM Account WHERE AccountNumber='"<<accountNum<<"' AND ExpirationDate > DATE('now');";

    return readRecord(ss.str());

}
bool ATMcard::verifyPin(){
    long long accountNum = getAcctNum();
    int accountPin = getAcctPin();
    if (accountNum == 0 || accountPin == 0) return false;

    stringstream ss;
    ss<<"SELECT Pin FROM Account WHERE AccountNumber='"<<accountNum<<"' AND Pin="<<accountPin<<";";

    return readRecord(ss.str());
}
//END VERIFICATION **********************

#ifndef ATMCARD_H
#define ATMCARD_H

#include "ATMsql.h"
#include <string>

using namespace std;


//inherit all public functions/variables in ATMsql class
class ATMcard: public ATMsql
{
    public:
        ATMcard();
        //~ATMcard();

        void setAcctNum(long long accNum);
        long long getAcctNum();

        /*
        void setExpDate(string expDate);
        string getExpDate();
        */

        void setAcctPin(int accPin);
        int getAcctPin();

        bool verifyAcctNum();
        bool verifyExpDate();
        bool verifyPin();

    private:
        long long acctNum;
        int balance;
        //string expiryDate;
        int pin;
};

#endif // ATMCARD_H

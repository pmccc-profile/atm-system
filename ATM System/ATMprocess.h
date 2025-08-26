#ifndef ATMPROCESS_H
#define ATMPROCESS_H

#include "ATMcard.h"
#include <string>


//inherit all public functions/variables in ATMsql class
class ATMprocess : public ATMcard
{
    public:
        ATMprocess();
        //~ATMprocess();

        bool balanceCheck(long long cardAcct);

        void setWithdrawalAmt(int withdrawAmt);
        int getWithdrawalAmt();

        void setDepositAmt(int depositAmt);
        int getDepositAmt();

        bool printReceipt(long long cardNumber, int t);

        //for withdraw and deposit
        bool updateBalance(char t);

    private:
        int withdrawAmount;
        int depositAmount;
};

#endif // ATMPROCESS_H

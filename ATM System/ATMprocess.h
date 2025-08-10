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

        void setWithdrawalAmt(int withdrawAmount);
        int getWithdrawalAmt();

        void setDepositAmt(int depositAmount);
        int getDepositAmt();

        bool printReceipt(long long cardNumber);

    private:
        int withdrawAmount;
};

#endif // ATMPROCESS_H

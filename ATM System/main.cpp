#include <iostream>
#include <sstream>
#include <cstdlib> //for generating rand()
#include <ctime>
#include <string>
#include <vector>

#include "ATMcard.h"
#include "ATMprocess.h"

using namespace std;


long long cardSimulation();

bool accountVerification(ATMcard &aCard);
bool pinVerification(ATMcard &aCard);
bool expDateVerification(ATMcard &aCard);

bool balanceCheck(ATMprocess &aProc);
void printOR(ATMprocess &aProc, long long cardAccount);
void withdraw(ATMprocess &aProc);
void deposit(ATMprocess &aProc);
int loopToMain();

int main(){

    cout<<"********************************************************************************************"<<endl;
    cout<<"TEMPORARILY PRINTS/DISPLAYS ALL DETAILS (SENSITIVE OR NOT) FOR CHECKING/TESTING PURPOSES."<<endl;
    cout<<"CURRENTLY FOCUSED ON FUNCTIONALITY."<<endl;
    cout<<"ONGOING DEVELOPMENT."<<endl;
    cout<<"********************************************************************************************"<<endl<<endl;

    ATMcard aCard;

    cout<<"WELCOME!"<<endl<<endl;

    //seed rand() to change each time
    srand(time(0));

    //aCard.readRecord("SELECT * FROM Account"); //for checking all records

    //CARD(S) SIMULATION FOR TESTING
    long long cardNum = cardSimulation();

    //set card account number (card inserted)
    aCard.setAcctNum(cardNum);

    //set card account number (card inserted)
    long long cardAccount = aCard.getAcctNum();

    //CODE FOR ATM VERIFICATION STARTS HERE:
    bool verifyAccount = accountVerification(aCard);
    bool isExpired = true;

    //verify card account number
    if(verifyAccount){

        int pin = 0;
        int pinAttempts = 1;
        bool pinCorrect = false;

        while(pinAttempts<=3){

            cout<<"Enter PIN: ";
            cin>>pin;

            //set card pin (card inserted)
            aCard.setAcctPin(pin);

            //verify card pin
            bool verifyPinNum = pinVerification(aCard);

            if(verifyPinNum){
                pinCorrect = true;
                break;
            }
            if(pinAttempts==3){
                cout<<"Account locked out."<<endl;
                break;
            }
            cout<<"Incorrect Pin.\nPlease try again."<<endl;
            pinAttempts++;
        }

        if(pinCorrect){
            //verify card expiration date
            bool verifyExpDate = expDateVerification(aCard);
            if(verifyExpDate){
                //proceed to ATM Process
                isExpired = false;
            }else{
               cout<<"Your card has expired.\nPlease visit the nearest branch for renewal."<<endl;
            }
        }
    }else{
        cout<<"Unrecognized account."<<endl;
    }

    //CODE FOR ATM PROCESSES STARTS HERE:
    ATMprocess aProc;

    aProc.setAcctNum(cardAccount);

    if(!isExpired){

        int ans_NewTransaction = 1;

        while(ans_NewTransaction == 1){

            int trans;

            cout<<"ATM Transactions"<<endl;
            cout<<"1.Balance"<<endl;
            cout<<"2.Withdraw"<<endl;
            cout<<"3.Deposit"<<endl;
            cout<<"4.Exit"<<endl;
            cout<<"Choose transaction: ";
            cin>>trans;

            switch(trans){
            case 1:
                aProc.balanceCheck(cardAccount);
                printOR(aProc, cardAccount);
                ans_NewTransaction = loopToMain();
                break;
            case 2:
                withdraw(aProc);
                printOR(aProc, cardAccount);
                ans_NewTransaction = 0;
                break;
            case 3:
                deposit(aProc);
                printOR(aProc, cardAccount);
                ans_NewTransaction = 0;
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<"Invalid input."<<endl;
            }
        }
    }

    cout<<"\n\nTHANK YOU!"<<endl<<endl;

    return 0;
}

long long cardSimulation(){
    //for random card simulation
    //long long (LL) due to 10-digit numbers
    vector<long long> cardNumber = {8291234567LL, 8297654321LL, 8299101112LL, 8299101113LL, 8299101114LL};

    //generate rand() number to access random card number vector
    int cardIndex = rand() % cardNumber.size();

    cout<<"Inserted Card: "<<cardNumber[cardIndex]<<endl<<endl;
    //cin>>cardNumber[cardIndex];

    long long cardNum = cardNumber[cardIndex];

    return cardNum;
}

bool accountVerification(ATMcard &aCard){
    if(aCard.verifyAcctNum()){
        return true;
    }else{
        return false;
    }
}

bool pinVerification(ATMcard &aCard){
    if(aCard.verifyPin()){
        return true;
    }else{
        return false;
    }
}

bool expDateVerification(ATMcard &aCard){
    if(aCard.verifyExpDate()){
        return true;
    }else{
        return false;
    }
}

void printOR(ATMprocess &aProc, long long cardAccount){
    int ans;
    cout<<"Do you want receipt?"<<endl;
    cout<<"1.Yes \t 2.No"<<endl;
    cout<<"Enter Number: ";
    cin>>ans;

    if(ans==1){
        cout<<"*******************************************************"<<endl;
        cout<<"                   BANK RECEIPT                        "<<endl;
        cout<<"*******************************************************"<<endl;
        aProc.printReceipt(cardAccount);
    }
}

void withdraw(ATMprocess &aProc){
    int withdrawAmt;
    char t = 'w'; //for withdraw

    cout<<"Withdraw Amount: ";
    cin>>withdrawAmt;

    //set withdrawal amount
    aProc.setWithdrawalAmt(withdrawAmt);

    bool withdrawSuccess = aProc.updateBalance(t);

    if(!withdrawSuccess){
        cout<<"Insufficient funds. Try Again"<<endl;
    }
}

void deposit(ATMprocess &aProc){
    int depositAmt;
    char t = 'd'; //for deposit

    cout<<"Deposit Amount: ";
    cin>>depositAmt;

    //set deposit amount
    aProc.setDepositAmt(depositAmt);

    bool depositSuccess = aProc.updateBalance(t);

    if(!depositSuccess){
        cout<<"Cannot deposit. Try Again"<<endl;
    }
}

int loopToMain(){
    int ansNewTransaction;
    cout<<"Do you want to perform another transaction?"<<endl;
    cout<<"1.Yes \t 2.No"<<endl;
    cout<<"Enter Number: ";
    cin>>ansNewTransaction;

    return ansNewTransaction;
}

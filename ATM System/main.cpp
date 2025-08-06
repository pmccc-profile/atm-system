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
    if(verifyAccount==true){

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

            if(verifyPinNum==true){
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
            if(verifyExpDate==true){
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

        int trans;

        cout<<"ATM Transactions"<<endl;
        cout<<"1.Balance Check"<<endl;
        cout<<"2.Withdraw Cash"<<endl;
        cout<<"Choose transaction: ";
        cin>>trans;

        switch(trans){
        case 1:
            aProc.balanceCheck(cardAccount);
            printOR(aProc, cardAccount);
            break;
        case 2:
            cout<<"A work in progress.";
        default:
            cout<<"Invalid input."<<endl;
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
        aProc.printReceipt(cardAccount);
    }else{
        cout<<"This part should loop to main menu or not? I'm sleepy."<<endl;
    }
}

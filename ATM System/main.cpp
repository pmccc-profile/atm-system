#include <iostream>
#include <sstream>
#include <cstdlib> //for generating rand() and clrscrn()
#include <ctime>
#include <string>
#include <vector>
#include <windows.h> //clrscrn()
#include <iomanip>
#include <conio.h> //getch

#include "ATMcard.h"
#include "ATMprocess.h"
#include "CenterScreen.h"


using namespace std;

long long cardSimulation();

bool accountVerification(ATMcard &aCard);
bool pinVerification(ATMcard &aCard);
bool expDateVerification(ATMcard &aCard);

bool balanceCheck(ATMprocess &aProc);
bool printOR(ATMprocess &aProc, long long cardAccount, int t);
bool withdraw(ATMprocess &aProc);
bool deposit(ATMprocess &aProc);
void clrscrn();
void positionCenter(const string &text);

int main(){

    ATMcard aCard;
    CenterScreen center;

    //seed rand() to change each time
    srand(time(0));

    //simulated card for testing
    long long cardNum = cardSimulation();

    int pin = 0;
    int pinAttempts = 0;
    bool isExpired = true;

    bool loopMain=true;

    do{
        clrscrn();

        cout<<endl<<endl;
        center.positionCenter("WELCOME!");
        cout<<endl<<endl;

        center.positionCenter("Simulated Card: "+ to_string(cardNum));
        cout<<endl<<endl;

        //set card account number (simulated card)
        aCard.setAcctNum(cardNum);

        //get card account number (simulated card)
        //long long cardAccount = aCard.getAcctNum();

        //aCard.readRecord("SELECT * FROM Account"); //for checking all records

        //CODE FOR ATM VERIFICATION STARTS HERE:
        center.positionCenter("-------------------------------------------------------");
        cout<<endl;
        center.positionCenter("SIMULATED CARD DETAILS (PURELY FOR TESTING/CHECKING)");
        cout<<endl;
        center.positionCenter("-------------------------------------------------------");
        cout<<endl;

        bool verifyAccount = accountVerification(aCard);

        cout<<endl;

        //verify card account number
        if(verifyAccount){

            while(pinAttempts<=3){

                center.positionCenter("Enter PIN: ");
                cin>>pin;

                //set card account pin
                aCard.setAcctPin(pin);

                bool verifyPinNum = pinVerification(aCard);

                //verify card acocunt pin
                if(verifyPinNum){
                    bool verifyExpDate = expDateVerification(aCard);

                    //verify card expiration date
                    if(verifyExpDate){
                        //card is still valid and not yet expired
                        isExpired = false;
                        loopMain = false;
                        break;
                    }else{
                        cout<<endl;
                        center.positionCenter("Your card has expired.");
                        cout<<endl;
                        center.positionCenter("Please visit the nearest branch for renewal.");
                        cout<<endl<<endl;
                        loopMain = false;
                        break;
                    }
                }else{
                    cout<<endl;
                    center.positionCenter("The PIN you entered is incorrect. Please try again.");
                    cout<<endl;
                    pinAttempts++;
                    getch(); //for pause before clrcsrn()
                    break;
                }
            }
            if(pinAttempts==3){
                cout<<endl;
                center.positionCenter("Your account has been locked out.");
                cout<<endl<<endl;
                loopMain = false;
                break;
            }
        }else{
            center.positionCenter("Unrecognized account.");
            cout<<endl<<endl;
            loopMain = false;
            break;
        }
    }while(loopMain);

    //CODE FOR ATM PROCESSES STARTS HERE:
    ATMprocess aProc;

    aProc.setAcctNum(cardNum);
    long long cardNumAcct = aProc.getAcctNum();

    if(!isExpired){

        bool loopTrans=true;

        do{
            clrscrn();

            bool printReceipt=false;
            int trans;

            center.positionCenter("--------------------------");
            cout<<endl;
            center.positionCenter("ATM Transactions");
            cout<<endl;
            center.positionCenter("--------------------------");
            cout<<endl;
            center.positionCenter("[1] Balance ");
            cout<<endl;
            center.positionCenter("[2] Withdraw");
            cout<<endl;
            center.positionCenter("[3] Deposit ");
            cout<<endl;
            center.positionCenter("[4] Exit    ");
            cout<<endl;
            center.positionCenter("--------------------------");
            cout<<endl;
            center.positionCenter("Choose transaction: ");
            cin>>trans;

            switch(trans){
                case 1:
                    clrscrn();
                    aProc.balanceCheck(cardNumAcct);
                    if(printOR(aProc, cardNumAcct, 1)) printReceipt = true;
                    break;
                case 2:
                    clrscrn();
                    //withdraw(aProc);
                    while(!withdraw(aProc)){
                        getch();
                        clrscrn();
                    }
                    if(printOR(aProc, cardNumAcct, 2)) printReceipt = true;
                    break;
                case 3:
                    clrscrn();
                    //deposit(aProc);
                    while(!deposit(aProc)){
                        getch();
                        clrscrn();
                    }
                    if(printOR(aProc, cardNumAcct, 3)) printReceipt = true;
                    break;
                case 4:
                    cout<<endl;
                    loopTrans=false;
                    break;
                default:
                    center.positionCenter("Invalid input.");
                    cout<<endl;
            }

            if(loopTrans){

                if(printReceipt) getch();

                clrscrn();

                int newTrans;

                cout<<endl<<endl;
                center.positionCenter("Would you like to perform another transaction?");
                cout<<endl;
                center.positionCenter("1.Yes \t 2.No");
                cout<<endl<<endl;
                center.positionCenter("Enter Number: ");
                cin>>newTrans;

                if(newTrans==2){
                    loopTrans=0;
                    cout<<endl<<endl;
                    break;
                }
            }else{
                break;
            }

        }while(loopTrans);
    }
    center.positionCenter("-------------------------------------------------------");
    cout<<endl;
    center.positionCenter("REVERTED TO DEFAULT (PURELY FOR TESTING/CHECKING)");
    cout<<endl;
    center.positionCenter("-------------------------------------------------------");
    cout<<endl<<endl;
    center.positionCenter("THANK YOU!");
    cout<<endl;

    return 0;
}

//FUNCTIONS BELOW

long long cardSimulation(){

    //long long (LL) due to 10-digit numbers
    vector<long long> cardNumber = {8291234567LL, 8297654321LL, 8299101112LL, 8299101113LL, 8299101114LL};

    //generate rand() number to access random card number vector
    int cardIndex = rand() % cardNumber.size();

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

bool printOR(ATMprocess &aProc, long long cardAccount, int t){

    CenterScreen center;

    int transType = t;
    int ans;

    cout<<endl<<endl;
    center.positionCenter("Would you like to print a receipt?");
    cout<<endl;
    center.positionCenter("1.Yes \t 2.No");
    cout<<endl<<endl;
    center.positionCenter("Enter Number: ");
    cin>>ans;

    if(ans==1){
        clrscrn();
        center.positionCenter("*******************************************************");
        cout<<endl;
        center.positionCenter("BANK RECEIPT");
        cout<<endl;
        center.positionCenter("*******************************************************");
        cout<<endl;
        center.positionCenter("-------------------------------------------------------");
        cout<<endl;
        center.positionCenter("TRANSACTION RECORD");
        cout<<endl;
        center.positionCenter("-------------------------------------------------------");
        cout<<endl;
        aProc.printReceipt(cardAccount, transType);
        cout<<endl;
        center.positionCenter("*******************************************************");
        cout<<endl;
        center.positionCenter("THANK YOU FOR BANKING WITH US.");
        cout<<endl;
        center.positionCenter("*******************************************************");
        cout<<endl;

        return true;
    }

    return false;
}

bool withdraw(ATMprocess &aProc){

    CenterScreen center;

    int withdrawAmt;
    char t = 'w'; //for withdraw

    cout<<endl<<endl;
    center.positionCenter("Withdraw Amount: ");
    cin>>withdrawAmt;

    //set withdrawal amount
    aProc.setWithdrawalAmt(withdrawAmt);

    bool withdrawSuccess = aProc.updateBalance(t);

    if(!withdrawSuccess){
        cout<<endl<<endl;
        center.positionCenter("Insufficient funds. Try Again");
        cout<<endl;

        return false;
    }

    return true;
}

bool deposit(ATMprocess &aProc){

    CenterScreen center;

    int depositAmt;
    char t = 'd'; //for deposit

    cout<<endl<<endl;
    center.positionCenter("Deposit Amount: ");
    cin>>depositAmt;

    //set deposit amount
    aProc.setDepositAmt(depositAmt);

    bool depositSuccess = aProc.updateBalance(t);

    if(!depositSuccess){
        cout<<endl<<endl;
        center.positionCenter("Cannot deposit. Try Again");
        cout<<endl;

        return false;
    }

    return true;
}

void clrscrn(){
#ifdef  _WIN32
    //for windows
    system("cls");
#else
    system("clear");
#endif
}

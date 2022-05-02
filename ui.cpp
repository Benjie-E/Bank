#include <iostream>
#include <iomanip>
#include <vector>

#include "accounts.h"
#include "tellers.h"
#include "ui.h"
#include "transaction.h"

using namespace std;

int UI::GetNumberFromUser(int minValue, int maxValue){
    int value;
    
    do{
        cout << "=>";
        cin >> value;
    } while(value <= minValue || value >= maxValue);
    string junkNewLine{};
    getline(cin, junkNewLine);
    return value;
}

float UI::GetCurrencyFromUser(){
    float value;
    cin >> value;
    string junkNewLine{};
    getline(cin, junkNewLine);
    return value;
}

string UI::GetAccountNumberFromUser(){
    string accountNumber{""};
    cout << "Account Number: ";
    getline(cin, accountNumber);
    return accountNumber;
}

bool UI::LoginUser(){
    string username;
    string password;

    cout << "Username:";
    username = UI::SafeGetLine();
    cout << "Password:";
    password = UI::SafeGetLine();
    Teller teller = Teller(username, password);
    return Login(teller);
}

void UI::AddAccount(){
    string accountNumber = UI::GetAccountNumberFromUser();
    if(AccountManager::IsValidAccount(accountNumber)){
        cout <<"Account number already exists" << endl;
        return;
    }

    string ssn {""};
    string name {""};
    string address {""};
    string phone {""};

    cout << "SSN: ";
    ssn = UI::SafeGetLine();
    cout << "Name: ";
    name = UI::SafeGetLine();
    cout << "Address: ";
    address = UI::SafeGetLine();
    cout << "Phone: ";
    phone = UI::SafeGetLine();

    AccountManager::AddAccount(accountNumber, ssn, name, address, phone);
}

void UI::DeleteAccount(){
    string accountNumber = UI::GetAccountNumberFromUser();

    if(!AccountManager::IsValidAccount(accountNumber)){
        cout<<"Account not found" << endl;
        return;
    }

    AccountManager::DeleteAccount(AccountManager::GetAccount(accountNumber));
    cout<<"Account deleted" <<endl;
}

void UI::UpdateAccount(){
    string accountNumber = UI::GetAccountNumberFromUser();

    Account account = AccountManager::GetAccount(accountNumber);

    string name {""};

    cout << "Name: ";
    name = UI::SafeGetLine();
    
    AccountManager::UpdateAccount(account, name);
    cout<<"Account updated" <<endl;
}

void UI::ViewAccount(){
    string accountNumber = UI::GetAccountNumberFromUser();
   
   /* if(!AccountManager::IsValidAccount(accountNumber)){
        cout<<"Account not found" << endl;
        return;
    }*/
    Account account;
    try{
         account= AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }
    

    cout << setw(10) << right << "SSN:" << account.ssn << endl;
    cout << setw(10) << right << "Name: " << account.name << endl;
    cout << setw(10) << right << "Address: " << account.address << endl;
    cout << setw(10) << right << "Phone: " << account.phone << endl;
    cout << setw(10) << right << "Balance: " << setprecision(2) << fixed << account.GetBalance() << endl;
}

void UI::ViewTransactions() {
    string accountNumber = UI::GetAccountNumberFromUser();
    extern const string PATH_PREFIX;
    vector<Transaction*> transactions = TransactionManager::extractTransactions(PATH_PREFIX + accountNumber + "-t.dat");
    for (Transaction *t : transactions) {
        cout << t->print()<<endl;
    }
}

void UI::DepositUI(){
    string accountNumber = UI::GetAccountNumberFromUser();

    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }
    float currentBalance = account.GetBalance();
    float depositAmount {0.0};
    
    cout<< "Current Balance: " << setprecision(2) << fixed << currentBalance << endl;
    cout<< "Deposit Amount: ";
    depositAmount = UI::GetCurrencyFromUser();

    Transaction *toFile = new Deposit(depositAmount);
    AccountManager::AddTransaction(account, toFile);
    delete toFile;

    AccountManager::UpdateBalance(account, currentBalance+depositAmount);
    cout << "Balance Updated: " << setprecision(2) << fixed << account.GetBalance() << endl;
}

void UI::WithdrawlUI(){
    string accountNumber = UI::GetAccountNumberFromUser();
    
    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }
    

    float currentBalance = account.GetBalance();
    float widthdrawAmount {0.0};
    
    cout<< "Current Balance: " << setprecision(2) << fixed << currentBalance << endl;
    cout<< "Withdrawl Amount: ";
    widthdrawAmount = UI::GetCurrencyFromUser();

    Transaction *toFile= new Withdrawl(widthdrawAmount);
    AccountManager::AddTransaction(account, toFile);
    delete toFile;
    AccountManager::UpdateBalance(account, currentBalance - widthdrawAmount);
    cout << "Balance Updated: " << setprecision(2) << fixed << account.GetBalance() << endl;
}

void UI::AccountMenu(){
    enum OPTIONS {
        MIN = 0,
        ADD,
        DELETE,
        UPDATE,
        VIEW,
        TRANSACTIONS,
        DEPOSIT,
        WITHDRAW,
        RETURN,
        MAX
    };

    int value;
    do{
        cout << OPTIONS::ADD    << "- Add account" << endl;
        cout << OPTIONS::DELETE << "- Delete account" <<endl;
        cout << OPTIONS::UPDATE << "- Update account" << endl;
        cout << OPTIONS::VIEW << "- View account" << endl;
        cout << OPTIONS::TRANSACTIONS << "- View transactions" << endl;
        cout << OPTIONS::DEPOSIT << "- Deposit" << endl;
        cout << OPTIONS::WITHDRAW << "- Withdraw" << endl;
        cout << OPTIONS::RETURN << "- Return" << endl;
        value = UI::GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);

        switch(value){
            case OPTIONS::ADD:
                UI::AddAccount();
                break;
            case OPTIONS::DELETE:
                UI::DeleteAccount();
                break;
            case OPTIONS::UPDATE:
                UI::UpdateAccount();
                break;
            case OPTIONS::VIEW:
                UI::ViewAccount();
                break;
            case OPTIONS::TRANSACTIONS:
                UI::ViewTransactions();
                break;
            case OPTIONS::DEPOSIT:
                UI::DepositUI();
                break;
            case OPTIONS::WITHDRAW:
                UI::WithdrawlUI();
                break;
        }
 
    } while(value != OPTIONS::RETURN);

}

void UI::MainMenu(){
    enum OPTIONS {
        MIN = 0,
        LOGIN =1,
        EXIT =2,
        MAX
    };

    int value;
    do{
        cout <<OPTIONS::LOGIN <<" - Login" << endl;
        cout <<OPTIONS::EXIT  <<" - Exit " << endl;

        value = UI::GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);
        switch(value){
            case OPTIONS::LOGIN:
                if(LoginUser()){
                    UI::AccountMenu();
                } else{
                    cout <<"Invalid Login" << endl;
                }
                break;
        }
    }while(value != OPTIONS::EXIT);
}

string UI::SafeGetLine(){
    string value {""};
    getline(cin, value);
    return value;
}
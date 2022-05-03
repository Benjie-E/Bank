/*
 Author:       Benjie
 Class:        CSI-240-03
 Assignment:   BankingFinalProject
 Due Date:     5/3/2022 14:30
 Description: Bank
 Dynamic Array Challenge
 Certification of Authenticity:
 I certify that this is entirely my own work, except where I have given
 fully-documented references to the work of others. I understand the
 definition and consequences of plagiarism and acknowledge that the assessor
 of this assignment may, for the purpose of assessing this assignment:
 - Reproduce this assignment and provide a copy to another member of
 academic staff; and/or
 - Communicate a copy of this assignment to a plagiarism checking
 service (which may then retain a copy of this assignment on its
 database for the purpose of future plagiarism checking)
 */
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
    
    do {
        cout << "=>";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
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

    do {
        cout << "SSN: ";
        ssn = UI::SafeGetLine();
    } while (!AccountManager::ValidSSN(ssn));
    cout << "Name: ";
    name = UI::SafeGetLine();
    cout << "Address: ";
    address = UI::SafeGetLine();
    do {
        cout << "Phone: ";
        phone = UI::SafeGetLine();
    } while (!AccountManager::ValidPhone(phone));
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
    enum OPTIONS {
        MIN = 0,
        SSN,
        NAME,
        ADDRESS,
        PHONE,
        RETURN,
        MAX
    };

    int value;
    do {
        cout << OPTIONS::SSN << "- Update SSN" << endl;
        cout << OPTIONS::NAME << "- Update name" << endl;
        cout << OPTIONS::ADDRESS << "- Update address" << endl;
        cout << OPTIONS::PHONE << "- Update phone number" << endl;
        
        cout << OPTIONS::RETURN << "- Return" << endl;
        value = UI::GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);

        switch (value) {
        case OPTIONS::SSN:
            UI::UpdateSSN();
            break;
        case OPTIONS::NAME:
            UI::UpdateName();
            break;
        case OPTIONS::ADDRESS:
            UI::UpdateAddress();
            break;
        case OPTIONS::PHONE:
            UI::UpdatePhone();
            break;
        }
    } while (value != OPTIONS::RETURN);
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
    
    enum OPTIONS {
        MIN = 0,
        ALL,
        DEPOSITS,
        WITHDRAWLS,
        RETURN,
        MAX
    };

    int value;
    do {
        cout << OPTIONS::ALL << "- Show all transactions" << endl;
        cout << OPTIONS::DEPOSITS << "- Show only deposits" << endl;
        cout << OPTIONS::WITHDRAWLS << "- Show only withdrawls" << endl;
        cout << OPTIONS::RETURN << "- Return" << endl;
        value = UI::GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);

        switch (value) {
        case OPTIONS::ALL:
            for (Transaction* t : transactions) {
                cout << t->print() << endl;
            }
            break;
        case OPTIONS::DEPOSITS:
            for (Transaction* t : transactions) {
                if (t->type = DEPOSIT) {
                    cout << t->print() << endl;
                }
            }
            break;
        case OPTIONS::WITHDRAWLS:
            for (Transaction* t : transactions) {
                if (t->type = WITHDRAWL) {
                    cout << t->print() << endl;
                }
            }
            break;
        }
    } while (value != OPTIONS::RETURN);
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
    while (depositAmount < 0) {
        cout << "Please enter a positive value" << endl;
        depositAmount = UI::GetCurrencyFromUser();
    }
    if (currentBalance + depositAmount < 0) {
        cout << "Insufficient funds" << endl;
        return;
    }
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
    float withdrawAmount {0.0};
    
    cout<< "Current Balance: " << setprecision(2) << fixed << currentBalance << endl;
    cout<< "Withdrawl Amount: ";
    withdrawAmount = UI::GetCurrencyFromUser();
    while (withdrawAmount < 0) {
        cout << "Please enter a positive value" << endl;
        withdrawAmount = UI::GetCurrencyFromUser();
    }
    if (currentBalance - withdrawAmount < 0) {
        cout << "Insufficient funds" << endl;
        return;
    }
    Transaction *toFile= new Withdrawl(withdrawAmount);
    AccountManager::AddTransaction(account, toFile);
    delete toFile;
    AccountManager::UpdateBalance(account, currentBalance - withdrawAmount);
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

void UI::UpdateName()
{
    string accountNumber = UI::GetAccountNumberFromUser();

    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }

    string name{ "" };

    cout << "Name: ";
    name = UI::SafeGetLine();
    account.name = name;
    cout << AccountManager::UpdateAccount(account) ? "Account updated" : "Update failed";
}

void UI::UpdateSSN()
{
    string accountNumber = UI::GetAccountNumberFromUser();

    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }

    string ssn{ "" };
    do {
        cout << "SSN: ";
        ssn = UI::SafeGetLine();
    } while (!AccountManager::ValidSSN(ssn));
    account.ssn = ssn;
    AccountManager::UpdateAccount(account);
    cout << AccountManager::UpdateAccount(account) ? "Account updated" : "Update failed";
}

void UI::UpdatePhone()
{
    string accountNumber = UI::GetAccountNumberFromUser();

    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }

    string phone{ "" };
    do {
        cout << "Phone: ";
        phone = UI::SafeGetLine();
    } while (!AccountManager::ValidPhone(phone));
    

    account.phone = phone;
    AccountManager::UpdateAccount(account);
    cout << AccountManager::UpdateAccount(account) ? "Account updated" : "Update failed";
}

void UI::UpdateAddress()
{
    string accountNumber = UI::GetAccountNumberFromUser();
    Account account;
    try {
        account = AccountManager::GetAccount(accountNumber);
    }
    catch (exception& e) {
        std::cout << e.what() << endl;
        return;
    }

    string address{ "" };

    cout << "Address: ";
    address = UI::SafeGetLine();
    account.address = address;
    AccountManager::UpdateAccount(account);
    cout << AccountManager::UpdateAccount(account) ? "Account updated" : "Update failed";
}

string UI::SafeGetLine(){
    string value {""};
    getline(cin, value);
    return value;
}
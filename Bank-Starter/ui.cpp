#include <iostream>
#include <iomanip>

#include "accounts.h"
#include "tellers.h"
#include "ui.h"

using namespace std;

int GetNumberFromUser(int minValue, int maxValue){
    int value;
    
    do{
        cout << "=>";
        cin >> value;
    } while(value <= minValue || value >= maxValue);
    string junkNewLine{};
    getline(cin, junkNewLine);
    return value;
}

float GetCurrencyFromUser(){
    float value;
    cin >> value;
    string junkNewLine{};
    getline(cin, junkNewLine);
    return value;
}

string GetAccountNumberFromUser(){
    string accountNumber{""};
    cout << "Account Number: ";
    getline(cin, accountNumber);
    return accountNumber;
}

bool LoginUser(){
    string username;
    string password;

    cout << "Username:";
    username = SafeGetLine();
    cout << "Password:";
    password = SafeGetLine();

    return Login(username, password);
}

void AddAccount(){
    string accountNumber = GetAccountNumberFromUser();
    //flip this
    try{
    Account test = LoadAccount(accountNumber);
    }catch(string s){
    	cout << s;
    }
    string ssn {""};
    string name {""};
    string address {""};
    string phone {""};

    cout << "SSN: ";
    ssn = SafeGetLine();
    cout << "Name: ";
    name = SafeGetLine();
    cout << "Address: ";
    address = SafeGetLine();
    cout << "Phone: ";
    phone = SafeGetLine();

    AddAccount(accountNumber, ssn, name, address, phone);
}

void DeleteAccount(){
    string accountNumber = GetAccountNumberFromUser();

    try{
       Account test = LoadAccount(accountNumber);
       }catch(string s){
       	cout << s;
       	return;
       }

    test.DeleteAccount(accountNumber);
    cout<<"Account deleted" <<endl;
}

void UpdateAccount(){
    string accountNumber = GetAccountNumberFromUser();

    if(!IsValidAccount(accountNumber)){
        cout<<"Account not found" << endl;
        return;
    }

    string name {""};

    cout << "Name: ";
    name = SafeGetLine();
    
    UpdateAccount(accountNumber, name);
    cout<<"Account updated" <<endl;
}

void ViewAccount(){
    string accountNumber = GetAccountNumberFromUser();
   
//    if(!IsValidAccount(accountNumber)){
//        cout<<"Account not found" << endl;
//        return;
//    }
    Account a = Account::GetAccount(accountNumber);
    cout << setw(10) << right << "SSN:" << a.ssn << endl;
    cout << setw(10) << right << "Name: " << a.name << endl;
    cout << setw(10) << right << "Address: " << a.address << endl;
    cout << setw(10) << right << "Phone: " << a.phone << endl;
    cout << setw(10) << right << "Balance: " << setprecision(2) << fixed << a.GetBalance() << endl;
}

void Deposit(){
    string accountNumber = GetAccountNumberFromUser();

    Account a = LoadAccount(accountNumber);

    float currentBalance = a.GetBalance();
    float depositAmount {0.0};
    
    cout<< "Current Balance: " << setprecision(2) << fixed << currentBalance << endl;
    cout<< "Deposit Amount: ";
    depositAmount = GetCurrencyFromUser();
    a.UpdateBalance(currentBalance+depositAmount);
    cout << "Balance Updated: " << setprecision(2) << fixed << a.GetBalance() << endl;
}

void Withdraw(){
    string accountNumber = GetAccountNumberFromUser();
    
    Account a = LoadAccount(accountNumber);

    float currentBalance = a.GetBalance();
    float widthdrawAmount {0.0};
    
    cout<< "Current Balance: " << setprecision(2) << fixed << currentBalance << endl;
    cout<< "Deposit Amount: ";
    widthdrawAmount = GetCurrencyFromUser();
    a.UpdateBalance(currentBalance - widthdrawAmount);
    cout << "Balance Updated: " << setprecision(2) << fixed << a.GetBalance() << endl;
}

void AccountMenu(){
    enum OPTIONS {
        MIN = 0,
        ADD,
        DELETE,
        UPDATE,
        VIEW,
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
        cout << OPTIONS::DEPOSIT << "- Deposit" << endl;
        cout << OPTIONS::WITHDRAW << "- Withdraw" << endl;
        cout << OPTIONS::RETURN << "- Return" << endl;
        value = GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);

        switch(value){
            case OPTIONS::ADD:
                AddAccount();
                break;
            case OPTIONS::DELETE:
                DeleteAccount();
                break;
            case OPTIONS::UPDATE:
                UpdateAccount();
                break;
            case OPTIONS::VIEW:
                ViewAccount();
                break;
            case OPTIONS::DEPOSIT:
                Deposit();
                break;
            case OPTIONS::WITHDRAW:
                Withdraw();
                break;
        }
 
    } while(value != OPTIONS::RETURN);

}

void MainMenu(){
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

        value = GetNumberFromUser(OPTIONS::MIN, OPTIONS::MAX);
        switch(value){
            case OPTIONS::LOGIN:
                if(LoginUser()){
                    AccountMenu();
                } else{
                    cout <<"Invalid Login" << endl;
                }
                break;
        }
    }while(value != OPTIONS::EXIT);
}

string SafeGetLine(){
    string value {""};
    getline(cin, value);
    return value;
}

Account LoadAccount(string accountId){

}

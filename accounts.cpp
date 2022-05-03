#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "accounts.h"
using namespace std;

extern const string PATH_PREFIX = "data/";
const string ACCOUNT_FILE_NAME = PATH_PREFIX + "accounts.dat";

void AccountManager::AddAccount(string accountNumber, string ssn, string name, string address, string phone){
    ofstream fout;
    fout.open(ACCOUNT_FILE_NAME, ios::app );

    fout << accountNumber << endl;
    fout << ssn << endl;
    fout << name << endl;
    fout << address << endl;
    fout << phone <<endl;

    fout.close();
}

bool AccountManager::UpdateAccount(Account account){
    ifstream fin(ACCOUNT_FILE_NAME);
    // we'll rewrite out file to here since we have it open
    // when done, overwrite with the stringstream data.
    stringstream sout;
    bool done = false;
    while(!fin.eof()){
        string _accountNumber {""};
        string _ssn {""};
        string _name {""};
        string _address {""};
        string _phone {""};

        getline(fin, _accountNumber);
        getline(fin, _ssn);
        getline(fin, _name);
        getline(fin, _address);
        getline(fin, _phone);

        if (_accountNumber == account.accountNumber) {
            done = true;
        }
        sout << _accountNumber << endl;
        sout << (_accountNumber == account.accountNumber ? account.ssn : _ssn) << endl;
        sout << (_accountNumber == account.accountNumber ? account.name : _name) << endl;
        sout << (_accountNumber == account.accountNumber ? account.address : _address) << endl;
        sout << (_accountNumber == account.accountNumber ? account.phone : _phone) <<endl;
    }

    fin.close();

    ofstream fout;
    fout.open(ACCOUNT_FILE_NAME);
    fout << sout.str();
    fout.close();
    return done;
}

float Account::GetBalance(){
    ifstream fin (PATH_PREFIX +  accountNumber + ".dat");

    
    // If the file does not exist, assume a balance of zero
    if(fin.fail())
    {
        std::cout << accountNumber << endl;
        return 0;
    }
    else 
    {
        float balance;
        fin >> balance;
        fin.close();
        return balance;
    }
}

void AccountManager::UpdateBalance(Account account, float balance){
    ofstream fout(PATH_PREFIX +  account.accountNumber + ".dat");
    fout << balance << endl;
    fout.close();
}

void AccountManager::DeleteAccount(Account account)
{
    ifstream fin;
    fin.open(ACCOUNT_FILE_NAME);

    stringstream sout;

    while(!fin.eof()){
        string accountNumber {""};
        string ssn {""};
        string name {""};
        string address {""};
        string phone {""};

        getline(fin, accountNumber);
        getline(fin, ssn);
        getline(fin, name);
        getline(fin, address);
        getline(fin, phone);

        if(account.accountNumber != accountNumber){
            sout << accountNumber << endl;
            sout << ssn << endl;
            sout << name << endl;
            sout << address << endl;
            sout <<phone <<endl;
        }
    }
    fin.close();

    ofstream fout;
    fout.open(ACCOUNT_FILE_NAME);
    fout << sout.str();
    fout.close();
}

Account AccountManager::GetAccount(string accountNumber){
    if (!IsValidAccount(accountNumber)) {
        throw(exception("Account_Does_Not_Exist"));
    }
    ifstream fin(ACCOUNT_FILE_NAME);


    while(!fin.eof()) {
        string _accountNumber {""};
        string _ssn {""};
        string _name {""};
        string _address {""};
        string _phone {""};

        getline(fin, _accountNumber);

        //deal with pesky newlines at end of file
        if(accountNumber == "") break;

        getline(fin, _ssn);
        getline(fin, _name);
        getline(fin, _address);
        getline(fin, _phone);

        if(_accountNumber == accountNumber){
            Account returnedAccount = Account();
            returnedAccount.accountNumber = accountNumber;
            returnedAccount.ssn  = _ssn;
            returnedAccount.name = _name;
            returnedAccount.address = _address;
            returnedAccount.phone = _phone;
            return returnedAccount;
            fin.close();
        }
    }
    fin.close();
    throw(exception("Account_Does_Not_Exist"));
}

bool AccountManager::IsValidAccount(string accountId){
    ifstream fin;
    fin.open(ACCOUNT_FILE_NAME);

    while(!fin.eof()){
        string file_accountId;
        string DataWeDoNotCareAbout;

        getline(fin, file_accountId);    //        01481

        if(file_accountId == "") break;

        getline(fin, DataWeDoNotCareAbout);//        554-00-8336
        getline(fin, DataWeDoNotCareAbout);//        Jane Jones
        getline(fin, DataWeDoNotCareAbout);//        1483 N. RealmSecond Ave., Burlington, VT 05401
        getline(fin, DataWeDoNotCareAbout);//        564 425 5052

        if(accountId == file_accountId)
        {
            return true;
        }
    }
    return false;
}

void AccountManager::AddTransaction(Account account, Transaction *transaction) {
    ofstream fout;
    fout.open(PATH_PREFIX + account.accountNumber + "-t.dat", ios::app);
    fout << transaction->printToFile();
    fout.close();
}

bool AccountManager::ValidSSN(string ssn)
{
    if (!std::regex_match(ssn, regex("[[:digit:]]{3}-[[:digit:]]{2}-[[:digit:]]{4}"))) {
        cout << "Invalid SSN" << endl;
        cout << "Try XXX-XX-XXXX" << endl;
        return false;
    }
    return true;
}

bool AccountManager::ValidPhone(string phone)
{
    if (!std::regex_match(phone, regex("[[:digit:]]{3}-[[:digit:]]{3}-[[:digit:]]{4}"))) {
        cout << "Invalid Phone Number" << endl;
        cout << "Try XXX-XXX-XXXX" << endl;
        return false;
    }
    return true;
}

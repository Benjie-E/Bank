#include <string>
#include <fstream>
#include <sstream>

#include "accounts.h"
using namespace std;

const string PATH_PREFIX = "data/";
const string ACCOUNT_FILE_NAME = PATH_PREFIX + "accounts.dat";

void AddAccount(string accountNumber, string ssn, string name, string address, string phone){

    ofstream fout;
    fout.open(ACCOUNT_FILE_NAME, ios::app );

    fout << accountNumber << endl;
    fout << ssn << endl;
    fout << name << endl;
    fout << address << endl;
    fout << phone <<endl;

    fout.close();
}

void UpdateAccount(string accountNumber, string newName){
    ifstream fin(ACCOUNT_FILE_NAME);

    // we'll rewrite out file to here since we have it open
    // when done, overwrite with the stringstream data.
    stringstream sout;

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

        sout << _accountNumber << endl;
        sout << _ssn << endl;
        sout << (_accountNumber == accountNumber ? newName : _name) << endl;
        sout << _address << endl;
        sout << _phone <<endl;
    }

    fin.close();

    ofstream fout;
    fout.open(ACCOUNT_FILE_NAME);
    fout << sout.str();
    fout.close();
}

float Account::GetBalance(){
    ifstream fin (PATH_PREFIX +  accountId + ".dat");

    // If the file does not exist, assume a balance of zero
    if(fin.fail())
    {
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

void UpdateBalance(string accountId, float balance){
    ofstream fout(PATH_PREFIX +  accountId + ".dat");
    fout << balance << endl;
    fout.close();
}

void DeleteAccount(string accountToDelete)
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

        if(accountToDelete != accountNumber){
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

Account Account::GetAccount(std::string accountNumber){
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
        	Account a=Account(_accountNumber,_ssn,_name,_address,_phone);
        	fin.close();
        	return a;
        }
    }
    fin.close();
    throw string("invalidAccount");
}

bool IsValidAccount(string accountId){
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

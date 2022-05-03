#include "transaction.h"
#include <iostream>
using namespace std;
string Withdrawl::printToFile() {
    stringstream sout;
    sout << "W" << endl;
    sout << this->amount << endl;
    sout << this->date << endl;
    sout << this->checkNumber << endl;
    return sout.str();

};
string Deposit::printToFile() {
    std::stringstream sout;
    sout << "D" << endl;
    sout << this->date << endl;
    sout << this->amount << endl;
    return sout.str();
};

std::vector<Transaction*> TransactionManager::extractTransactions(string path) {
    
    vector<Transaction*> transactions;
    ifstream fin(path);

    if (!fin.good()) {
        fin.close();
        std::cout << "No transactions for this account" << endl;
        return transactions;
    }
    while (!fin.eof()) {
        string _type{ "" };
        int _date{};
        float _amount{};
        int _checkNumber{};

        getline(fin, _type);

        //deal with pesky newlines at end of file
        //if (_type == "") break;
        if (_type == "W") {
            fin >> _date;
            fin >> _amount;
            fin >> _checkNumber;
            transactions.push_back(new Withdrawl(_amount,_date,_checkNumber));
        }
        if (_type == "D") {
            fin >> _date;
            fin >> _amount;
            transactions.push_back(new Deposit(_amount,_date));
        }
    }
    fin.close();
    return transactions;
}

std::string Withdrawl::print() {
    stringstream sout;
    sout << "Type: Withdrawl" << endl;
    sout << "Amount: " << setprecision(2) << fixed << amount << endl;
    sout << "Date: " << ctime(&date) << endl;
    sout << "Check Number: " << checkNumber << endl;
    return sout.str();
}
std::string Deposit::print() {
    stringstream sout;
    sout << "Type: Deposit" << endl;
    sout << "Amount: " << setprecision(2) << fixed << amount << endl;
    sout << "Date: " << ctime(&date) << endl;
    return sout.str();
}
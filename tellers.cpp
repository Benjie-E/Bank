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
#include <fstream>
#include <string>
#include "tellers.h"
using namespace std;
const string PATH_PREFIX = "data/";
const string TELLER_FILE_NAME="data/tellers.dat";

bool Login(Teller teller){

    if (teller.username == "" && teller.password == "") {
        return false;
    }
    bool success = false;

    ifstream fin(TELLER_FILE_NAME);

    if(fin.fail()){
        cerr << "Error opening << "<< TELLER_FILE_NAME <<" file." << endl;
        return false;
    }

    while(!fin.eof()){
        string file_username = "";
        string file_password = "";

        //format "username password {newline}"
        fin >> file_username;
        fin >> file_password;
        string junk_newline;
        getline(fin, junk_newline);

        if(file_username == teller.username && file_password == teller.password){
            success = true;

        }
    }

    return success;
}
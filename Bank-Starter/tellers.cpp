#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string TELLER_FILE_NAME="data/tellers.dat";

bool Login(string username, string password){
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

        //if(file_username == username && file_password == password){
        if(file_username == username){
            success = true;
        }
    }

    return success;
}

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
#pragma once
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
enum TransactionType {
	WITHDRAWL,
	DEPOSIT
};


class Transaction {
public:
	Transaction(TransactionType transactionType,float amount) {
		type = transactionType;
		this->amount = amount;
		date = time(0);
	}
	TransactionType type;
	time_t date;
	float amount;
	virtual std::string printToFile() = 0;
	virtual std::string print() = 0;
};

class Withdrawl : public Transaction{
public:
	Withdrawl(float amount) : Transaction(WITHDRAWL, amount) {};
	Withdrawl(float amount, time_t date, int checkNumber) : Transaction(WITHDRAWL, amount) { this->date = date, this->checkNumber = checkNumber; };
	int checkNumber;
	std::string printToFile();
	std::string print();
};

class Deposit : public Transaction{
public:
	Deposit(float amount) : Transaction(DEPOSIT, amount) {};
	Deposit(float amount, time_t date) : Transaction(DEPOSIT, amount) { this->date = date; };
	std::string printToFile();
	std::string print();
};

class TransactionManager {
public:
	static std::vector<Transaction*> extractTransactions(std::string path);
};

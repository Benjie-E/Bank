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

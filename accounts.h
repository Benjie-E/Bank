#pragma once

#include <string>
#include "transaction.h"
class Account {
public:
	std::string accountNumber;
	std::string ssn;
	std::string name;
	std::string address;
	std::string phone;
	float balance = GetBalance();
	float GetBalance();
};
class AccountManager {
public:
	static void AddAccount(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
	static Account GetAccount(std::string accountNumber);
	static void UpdateAccount(Account account, std::string name);
	static void UpdateBalance(Account account, float balance);
	static void DeleteAccount(Account account);
	static bool IsValidAccount(std::string accountNumber);
	static void AddTransaction(Account account, Transaction *transaction);
};


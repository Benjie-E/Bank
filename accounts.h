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
enum class UpdateType {
	name,
	ssn,
	phone,
	address
};
class AccountManager {
public:
	static void AddAccount(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
	static Account GetAccount(std::string accountNumber);
	static bool UpdateAccount(Account account);
	static void UpdateBalance(Account account, float balance);
	static void DeleteAccount(Account account);
	static bool IsValidAccount(std::string accountNumber);
	static void AddTransaction(Account account, Transaction *transaction);

	static bool ValidSSN(std::string ssn);
	static bool ValidPhone(std::string phone);
};


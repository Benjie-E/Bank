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
	void UpdateBalance(float balance);
	void operator+=(const float amount) { UpdateBalance(GetBalance()-amount); };
	void operator-=(const float amount) { UpdateBalance(GetBalance()-amount); };
	
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
	
	static void DeleteAccount(Account account);
	static bool IsValidAccount(std::string accountNumber);
	static void AddTransaction(Account account, Transaction *transaction);

	static bool ValidSSN(std::string ssn);
	static bool ValidPhone(std::string phone);
};


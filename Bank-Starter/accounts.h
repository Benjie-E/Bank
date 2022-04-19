#pragma once

#include <string>

class Account{
public:
	Account(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
	void AddAccount(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
	static Account GetAccount(std::string accountNumber);
	void UpdateAccount(std::string accountNumber, std::string name);
	float GetBalance();
	void UpdateBalance(float balance);
	//void DeleteAccount();
	//bool IsValidAccount();
	std::string accountId;
		float balance;
		std::string phone;
		std::string name;
		std::string address;
		std::string ssn;
private:

};

#pragma once

#include <string>

bool Login(std::string username, std::string password);

class AccountManager{
		void AddAccount(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
		static Account GetAccount(std::string accountNumber);
		void UpdateAccount(std::string accountNumber, std::string name);
		float GetBalance();
		void UpdateBalance(float balance);
		void DeleteAccount();
		bool IsValidAccount();
};

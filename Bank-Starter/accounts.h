#pragma once

#include <string>

void AddAccount(std::string accountNumber, std::string ssn, std::string name, std::string address, std::string phone);
void GetAccount(std::string accountNumber, std::string &ssn, std::string &name, std::string &address, std::string &phone);
void UpdateAccount(std::string accountNumber, std::string name);
float GetBalance(std::string accountId);
void UpdateBalance(std::string accountId, float balance);
void DeleteAccount(std::string accountToDelete);
bool IsValidAccount(std::string accountId);
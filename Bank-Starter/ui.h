#pragma once

#include <string>

using namespace std;

int GetNumberFromUser(int minValue, int maxValue);
string GetAccountNumberFromUser();
float GetCurrencyFromUser();
bool LoginUser();
void AddAccount();
void DeleteAccount();
void UpdateAccount();
void ViewAccount();
void Deposit();
void Withdraw();
void AccountMenu();
void MainMenu();
Account LoadAccount(string accountId);

std::string SafeGetLine();

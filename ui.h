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

using namespace std;
class UI {
public:
	static int GetNumberFromUser(int minValue, int maxValue);
	static string GetAccountNumberFromUser();
	static float GetCurrencyFromUser();
	static bool LoginUser();
	static void AddAccount();
	static void DeleteAccount();
	static void UpdateAccount();
	static void ViewAccount();
	static void ViewTransactions();
	static void DepositUI();
	static void WithdrawlUI();
	static void AccountMenu();
	static void MainMenu();

	static void UpdateName();
	static void UpdateSSN();
	static void UpdatePhone();
	static void UpdateAddress();

	static std::string SafeGetLine();
};

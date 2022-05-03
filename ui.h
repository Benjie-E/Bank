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

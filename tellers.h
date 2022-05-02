#pragma once

#include <string>

class Teller {
public:
	Teller(std::string username, std::string password) {
		this->username = username;this->password = password;
	};
	std::string username;
	std::string password;

};
bool Login(Teller teller);
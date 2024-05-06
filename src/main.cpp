// FILE: `src/main.cpp`
#include "Account.h"
#include "EnvReader.h"
#include <iostream>

int main() {
	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	Account myAccount(accountNumber, authToken, liveTrade);
	myAccount.fetchAccountDetails();

	return 0;
}
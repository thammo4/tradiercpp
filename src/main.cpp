// FILE: `src/main.cpp`
#include "Account.h"
#include "EnvReader.h"
#include <iostream>

int main() {
	//
	// Read authorization token, account number from Python-style environment file
	//

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	//
	// Instantiate Account class
	//

	Account myAccount(accountNumber, authToken, liveTrade);

	//
	// Retrieve general account information
	//

	myAccount.fetchAccountDetails();
	std::cout << "----------\n" << std::endl;

	//
	// Fetch balance details
	//

	myAccount.fetchBalances();
	std::cout << "----------\n" << std::endl;


	//
	// Fetch account gain/loss information
	//

	myAccount.getGainLoss();

	return 0;
}
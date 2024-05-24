// FILE: `src/main.cpp`
#include "Tradier.h"
#include "Account.h"
#include "EnvReader.h"
#include <iostream>
#include <thread>

int main() {
	//
	// Read authorization token, account number from Python-style environment file
	// tradier_acct_live
	//

	auto env = loadEnv("../.env");
	// std::string accountNumber = env["tradier_acct"];
	// std::string authToken = env["tradier_token"];
	std::string accountNumber = env["tradier_acct_live"];
	std::string authToken = env["tradier_token_live"];
	bool liveTrade = true;

	Tradier tradier(accountNumber, authToken, liveTrade);
	auto sessionResponse = tradier.startMarketSession();
	if (sessionResponse.contains("stream") && sessionResponse["stream"].contains("sessionid")) {
		std::string sessionId = sessionResponse["stream"]["sessionid"].get<std::string>();

		//
		// Initialize WebSocket in separate thread
		//

		std::thread wsThread([&tradier, sessionId]() {
			tradier.startWebSocket(sessionId);
		});
		wsThread.detach();


		// tradier.startWebSocket(sessionId);
	} else {
		std::cerr << "Failed to start market session [main]" << std::endl;
	}

	std::cout << sessionResponse << std::endl;
	std::cout << "----------\n" << std::endl;


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


	//
	// Fetch Current Positions
	//

	myAccount.getPositions();
	std::cout << "----------\n" << std::endl;

	return 0;
}
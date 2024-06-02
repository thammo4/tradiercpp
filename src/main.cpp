// FILE: `src/main.cpp`
#include "Tradier.h"
#include "Account.h"
#include "EnvReader.h"
#include "EquityOrder.h"
#include "OptionsOrder.h"
#include <iostream>
#include <thread>

int main() {
	//
	// Read authorization token, account number from Python-style environment file
	//
	//

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	//
	// Instantiate Account, EquityOrder classes
	//

	Account myAccount(accountNumber, authToken, liveTrade);
	EquityOrder equityOrder(accountNumber, authToken, liveTrade);
	OptionsOrder optionsOrder(accountNumber, authToken, liveTrade);


	//
	// Options Order to buy QQQ240604C00488000
	//

	std::string occSymbol = "QQQ240604C00488000";
	std::string orderType = "market";
	std::string side = "buy_to_open";
	int quantity = 10;
	std::string underlying = "QQQ";
	double limitPrice = 0.0;
	double stopPrice = 0.0;
	std::string duration = "day";

	std::cout << "!!!!!! OPTIONS ORDER !!!!!" << std::endl;

	auto response = optionsOrder.order(occSymbol, orderType, side, quantity, underlying, limitPrice, stopPrice, duration);
	std::cout << "Broker Response: " << response.dump(4) << std::endl;


	//
	// Order to buy Apple
	//

	std::cout << "\n----------\n" << std::endl;
	std::cout << "!!!!! EQUITY ORDER !!!!!" << std::endl;

	std::string symbol = "AAPL";
	std::string equitySide = "buy";
	// int quantity = 5;
	// // std::string quantity = "5";
	// std::string orderType = "market";

	try {
		auto response = equityOrder.order(symbol, equitySide, quantity, orderType);
		std::cout << "Broker Response: " << response.dump(4) << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception occurred: " << e.what() << std::endl;
	}

	return 0;
}

	// //
	// // Retrieve general account information
	// //

	// myAccount.fetchAccountDetails();
	// std::cout << "----------\n" << std::endl;

	// //
	// // Fetch balance details
	// //

	// myAccount.fetchBalances();
	// std::cout << "----------\n" << std::endl;


	// //
	// // Fetch account gain/loss information
	// //

	// myAccount.getGainLoss();


	// //
	// // Fetch Current Positions
	// //

	// myAccount.getPositions();
	// std::cout << "----------\n" << std::endl;
// }




//
// OUTPUT
//

// thammons@toms-MacBook-Air build % ./TradierCPP
// URL: https://sandbox.tradier.com/v1/accounts/VA36593574/orders
// JSON PARSE ERROR [json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - invalid literal; last read: '<'
// Broker Response: null
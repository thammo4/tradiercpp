// FILE: `src/main.cpp`
#include "Account.h"
#include "EnvReader.h"
#include "EquitiesData.h"
#include "EquityOrder.h"
#include "OptionsOrder.h"
#include "Tradier.h"
#include <iostream>
#include <thread>

int main() {

	//
	// Read authorization token, account number from Python-style environment file
	//

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	//
	// Instantiate Account, EquitiesData, EquityOrder, OptionsOrder classes
	//

	Account myAccount(accountNumber, authToken, liveTrade);
	EquityOrder equityOrder(accountNumber, authToken, liveTrade);
	OptionsOrder optionsOrder(accountNumber, authToken, liveTrade);
	EquitiesData equitiesData(accountNumber, authToken, liveTrade);

	//
	// Retrieve general account information
	//

	std::cout << "ACCOUNT DETAILS" << std::endl;
	myAccount.fetchAccountDetails();
	std::cout << "----------\n" << std::endl;

	//
	// Fetch balance details
	//

	std::cout << "ACCOUNT BALANCE DETAILS" << std::endl;
	myAccount.fetchBalances();
	std::cout << "----------\n" << std::endl;


	//
	// Fetch account gain/loss information
	//

	std::cout << "GAIN/LOSS INFORMATION" << std::endl;
	auto gainLoss = myAccount.getGainLoss();
	std::cout << gainLoss << std::endl;
	std::cout << "---------\n" << std::endl;


	//
	// Fetch Current Positions
	//

	std::cout << "CURRENT POSITIONS" << std::endl;
	auto positions = myAccount.getPositions();
	std::cout << positions << std::endl;
	std::cout << "----------\n" << std::endl;


	//
	// Fetch Current Quote for ConocoPhillips and Invesco QQQ Trust, Series 1
	//

	std::string symbolList = "COP,QQQ";
	auto copQuote = equitiesData.getQuotes(symbolList);
	std::cout << copQuote << std::endl;

	std::cout << "----------" << std::endl;

	std::cout << "COP" << std::endl;
	std::cout << copQuote[0] << std::endl;
	std::cout << "\n" << std::endl;

	std::cout << "QQQ" << std::endl;
	std::cout << copQuote[1] << std::endl;
	std::cout << "\n" << std::endl;


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

	try {
		auto response = equityOrder.order(symbol, equitySide, quantity, orderType);
		std::cout << "Broker Response: " << response.dump(4) << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception occurred: " << e.what() << std::endl;
	}

	return 0;
}
// FILE: `src/main_tradierqlib.cpp`
#include "EnvReader.h"
#include "EquitiesData.h"
#include "OptionsData.h"
#include "OptionsOrder.h"
#include "Tradier.h"

#include <iostream>
#include <ql/quantlib.hpp>


int main() {

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	EquitiesData equitiesData(accountNumber, authToken, liveTrade);
	OptionsData optionsData(accountNumber, authToken, liveTrade);
	OptionsOrder optionsOrder(accountNumber, authToken, liveTrade);

	//
	// Retrieve Stock/Option Data from Tradier
	//

	auto panwQuote = equitiesData.getQuotes("PANW");



	//
	// Define date/calendar parameters
	//

	QuantLib::Calendar calendar = QuantLib::TARGET();
	QuantLib::Date todaysDate = QuantLib::Date::todaysDate();
	QuantLib::Settings::instance().evaluationDate() = todaysDate;

	//
	// Define Option Parameters
	//

	QuantLib::Option::Type optionType(QuantLib::Option::Call);
	QuantLib::Real stockPrice = 0; 				// replace with real value
	QuantLib::Real strikePrice = 0; 			// replace with real value
	QuantLib::Spread dividendYield = 0.00; 		// replace with real value
	QuantLib::Rate riskFreeRate = 0.00; 		// replace with real value from FRED
	QuantLib::Volatility volatility = 0.20; 	// need to think about this one

	return 0;
}
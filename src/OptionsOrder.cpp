// FILE: `src/OptionsOrder.cpp`
#include "OptionsOrder.h"
#include <iostream>


//
// Constructor
//

OptionsOrder::OptionsOrder(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade) {
	ORDER_ENDPOINT = "/v1/accounts/" + accountNumber + "/orders";
}

OptionsOrder::~OptionsOrder() {}

nlohmann::json OptionsOrder::order(
	const std::string& occSymbol,
	const std::string& orderType,
	const std::string& side,
	int quantity,
	const std::string& underlying,
	double limitPrice,
	double stopPrice,
	const std::string& duration
) {
	std::ostringstream paramsStream;
	paramsStream << "class=option"
				 << "&symbol=" << underlying
				 << "&side=" << side
				 << "&option_symbol=" << occSymbol
				 << "&quantity=" << quantity
				 << "&type=" << orderType
				 << "&duration=" << duration;

	if ((orderType == "limit" || orderType == "stop_limit") && limitPrice > 0.0) 	{ paramsStream << "&price=" << limitPrice; }
	if ((orderType == "stop" || orderType == "stop_limit") && stopPrice > 0.0) 		{ paramsStream << "&stop=" << stopPrice; }

	std::string params = paramsStream.str();
	std::cout << "PARAMS [OptionsOrder] " << params << std::endl;

	return sendRequest(ORDER_ENDPOINT, "POST", params);

}
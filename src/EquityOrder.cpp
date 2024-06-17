// FILE: `src/EquityOrder.cpp`
#include <iostream>
#include "EquityOrder.h"

EquityOrder::EquityOrder(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade) {
	ORDER_ENDPOINT = "/v1/accounts/" + accountNumber + "/orders";
}

EquityOrder::~EquityOrder() {}


nlohmann::json EquityOrder::order(
	const std::string& symbol,
	const std::string& side,
	int quantity,
	const std::string& orderType,
	const std::string& duration,
	double limitPrice,
	double stopPrice
) {
	std::ostringstream paramsStream;
	paramsStream << "class=equity"
				 << "&symbol=" << symbol
				 << "&side=" << side
				 << "&quantity=" << quantity
				 << "&type=" << orderType
				 << "&duration=" << duration;

	if (orderType == "limit" || orderType == "stop_limit") 	{ paramsStream << "&price=" << limitPrice; }
	if (orderType == "stop" || orderType == "stop_limit") 	{ paramsStream << "&stop=" << stopPrice; }

	std::string params = paramsStream.str();

	std::cout << "PARAMS [EquityOrder] " << params << std::endl;

	return sendPostRequest(ORDER_ENDPOINT, params);
}
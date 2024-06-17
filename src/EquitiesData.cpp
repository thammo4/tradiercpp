// FILE: `src/EquitiesData.cpp`
#include <iostream>
#include "EquitiesData.h"

EquitiesData::EquitiesData(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade), QUOTES_ENDPOINT("/v1/markets/quotes") {
	// move along, nothing to see here.
}

EquitiesData::~EquitiesData() {}

nlohmann::json EquitiesData::getQuotes(const std::string& symbols) const {
	std::string endpoint = QUOTES_ENDPOINT + "?symbols=" + symbols;
	try {
		auto response = sendGetRequest(endpoint);
		return response["quotes"]["quote"];
	} catch (std::exception& e) {
		std::cerr << "Quote GET request no good: " << e.what() << std::endl;
		return nlohmann::json();
	}
}
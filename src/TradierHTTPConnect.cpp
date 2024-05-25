// FILE: `src/TradierHTTPConnect.cpp`
#include "Tradier.h"
#include <iostream>

nlohmann::json Tradier::startMarketSession() const {
	std::string endpoint = "/v1/markets/events/session";
	nlohmann::json response = sendPostRequest(endpoint, "{}");

	if (response.contains("stream") && response["stream"].contains("sessionid")) {
		std::cout << "HTTP Post Connect Successful." << std::endl;
		std::cout << "SessionId: " << response["stream"]["sessionid"] << std::endl;
	} else {
		std::cerr << "Failed stream connect:\n" << response.dump() << std::endl;
	}

	return response;
}

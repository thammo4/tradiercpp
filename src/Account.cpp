// FILE: `src/Account.cpp`
#include <iostream>
#include "Account.h"

Account::Account(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade) {

}


//
// Fetch general information about account
//


void Account::fetchAccountDetails() const {
	nlohmann::json userProfile = sendGetRequest("/v1/user/profile");
	std::cout << "USER PROF\n" << userProfile.dump(4) << std::endl;
}



//
// Retrieve account balance
//

void Account::fetchBalances() const {
	std::string endpoint = BALANCES_ENDPOINT;
	size_t pos = endpoint.find("{account_id}");

	if (pos != std::string::npos) {
		endpoint.replace(pos, std::string("{account_id}").length(), ACCOUNT_NUMBER);
	} else {
		std::cerr << "No account ID in URL string [fetchBalances]." << std::endl;
		return;
	}

	nlohmann::json balances = sendGetRequest(endpoint);
	std::cout << "BALANCES\n" << balances.dump(4) << std::endl;
}


//
// Get positional gains and losses
//

nlohmann::json Account::getGainLoss() const {
	std::string endpoint = GAIN_LOSS_ENDPOINT;
	size_t pos = endpoint.find("{account_id}");
	if (pos != std::string::npos) {
		endpoint.replace(pos, std::string("{account_id}").length(), ACCOUNT_NUMBER);
	} else {
		std::cerr << "No account ID in URL string [getGainLoss]." << std::endl;
		return {};
	}
	nlohmann::json gainLoss = sendGetRequest(endpoint);
	return gainLoss;
}




//
// Get account's current open positions
//

nlohmann::json Account::getPositions(const std::vector<std::string>& symbols, bool equities, bool options) const {
	std::string endpoint = POSITIONS_ENDPOINT;
	size_t pos = endpoint.find("{account_id}");

	nlohmann::json positions;

	if (pos != std::string::npos) {
		endpoint.replace(pos, std::string("{account_id}").length(), ACCOUNT_NUMBER);
		positions = sendGetRequest(endpoint);
	} else {
		std::cerr << "No account ID in URL string [getPositions]." << std::endl;
		positions = nlohmann::json();
	}
	return positions;
}
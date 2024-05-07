// FILE: `src/Account.cpp`

#include "Account.h"
#include <iostream>

Account::Account(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade) {

}


// void Account::fetchBalances() const {
// 	std::string endpoint = BALANCES_ENDPOINT;
// 	endpoint.replace(endpoint.find("{account_id}"), std::string("{account_id}").length(), accountNumber);
// 	nlohmann::json balances = sendGetRequest(endpoint);
// 	std::cout << "BALANCES\n" << balances.dump(4) << std::endl;
// }

void Account::fetchBalances() const {
	std::string endpoint = BALANCES_ENDPOINT;
	size_t pos = endpoint.find("{account_id}");

	if (pos != std::string::npos) {
		endpoint.replace(pos, std::string("{account_id}").length(), ACCOUNT_NUMBER);
	} else {
		std::cerr << "Cant find account ID in URL string" << std::endl;
		return;
	}

	nlohmann::json balances = sendGetRequest(endpoint);
	std::cout << "BALANCES\n" << balances.dump(4) << std::endl;
}

void Account::fetchAccountDetails() const {
	nlohmann::json userProfile = sendGetRequest("/v1/user/profile");
	std::cout << "USER PROF\n" << userProfile.dump(4) << std::endl;
}
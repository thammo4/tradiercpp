// FILE: `src/Account.cpp`

#include "Account.h"
#include <iostream>

Account::Account(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade) {

}

void Account::fetchAccountDetails() const {
	nlohmann::json userProfile = sendGetRequest("/v1/user/profile");
	std::cout << "USER PROF\n" << userProfile.dump(4) << std::endl;
}
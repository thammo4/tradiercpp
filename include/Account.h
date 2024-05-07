// FILE `include/Account.h`
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Tradier.h"
#include <string>

class Account : public Tradier {
public:
	Account(const std::string& accountNumber, const std::string& authToken, bool liveTrade=false);
	void fetchAccountDetails() const;
	void fetchBalances() const;
	nlohmann::json getGainLoss() const;
	nlohmann::json getPositions(const std::vector<std::string>& symbols={}, bool equities=false, bool options=false) const;

private:
	std::string accountNumber;
	std::string authToken;
	bool liveTrade;

	//
	// Define Account API Endpoints
	//

	const std::string ACCOUNT_DETAILS_ENDPOINT 		= "/v1/user/profile";
	const std::string BALANCES_ENDPOINT 			= "/v1/accounts/{account_id}/balances";
	const std::string POSITIONS_ENDPOINT 			= "/v1/accounts/{account_id}/positions";
	const std::string HISTORY_ENDPOINT 				= "/v1/accounts/{account_id}/history";
	const std::string GAIN_LOSS_ENDPOINT 			= "/v1/accounts/{account_id}/gainloss";
};

#endif
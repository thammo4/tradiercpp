// FILE `include/Account.h`
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Tradier.h"
#include <string>

class Account : public Tradier {
public:
	Account(const std::string& accountNumber, const std::string& authToken, bool liveTrade=false);
	void fetchAccountDetails() const;

private:
	std::string accountNumber;
	std::string authToken;
	bool liveTrade;
};

#endif
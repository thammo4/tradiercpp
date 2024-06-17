// FILE: `include/EquitiesData.h`
#ifndef EQUITIES_DATA_H
#define EQUITIES_DATA_H

#include <string>
#include "Tradier.h"

class EquitiesData : public Tradier {
public:
	EquitiesData(const std::string& accountNumber, const std::string& authToken, bool liveTrade);
	virtual ~EquitiesData();
	nlohmann::json getQuotes(const std::string& symbols) const;

private:
	std::string QUOTES_ENDPOINT;
};

#endif
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
	nlohmann::json getHistoricalQuotes(
		const std::string& symbol,
		const std::string& timeInterval,
		const std::string& startDate,
		const std::string& endDate,
		const std::string& sessionFilter = "all") const;

private:
	std::string QUOTES_ENDPOINT;
	std::string QUOTES_HISTORICAL_ENDPOINT;
};

#endif
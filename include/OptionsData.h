// FILE: `include/OptionsData.h`
#ifndef OPTIONS_DATA_H
#define OPTIONS_DATA_H

#include <string>
#include "Tradier.h"

class OptionsData : public Tradier {
public:
	OptionsData(const std::string& accountNumber, const std::string& authToken, bool liveTrade);
	virtual ~OptionsData();
	nlohmann::json getChain(const std::string& symbol, const std::string& expiry, const bool greekAndVol=false) const;
	nlohmann::json getStrikesForExpiry(const std::string& symbol, const std::string& expiry, const bool includeAllRoots=false) const; 
	nlohmann::json getOptionsContracts(const std::string& symbol, const bool strikePrice=false, const bool contractSize=false, const bool expiryFreq=false) const;
	nlohmann::json getOccsFromUnderlying(const std::string& symbol) const;

private:
	std::string OPTIONS_CHAINS_ENDPOINT;
	std::string OPTIONS_STRIKES_ENDPOINT;
	std::string OPTIONS_EXPIRIES_ENDPOINT;
	std::string OPTIONS_LOOKUP_ENDPOINT;
};

#endif
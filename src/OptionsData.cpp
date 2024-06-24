// FILE: `src/OptionsData.cpp`
#include <iostream>
#include "OptionsData.h"


//
// OptionsData Constructor
//

OptionsData::OptionsData (const std::string& accountNumber, const std::string& authToken, bool liveTrade)
	: Tradier(accountNumber, authToken, liveTrade),
	  OPTIONS_CHAINS_ENDPOINT("/v1/markets/options/chains"), 			// OptionsData::getChain
	  OPTIONS_STRIKES_ENDPOINT("/v1/markets/options/strikes"), 		// 
	  OPTIONS_EXPIRIES_ENDPOINT("/v1/markets/options/expirations"),
	  OPTIONS_LOOKUP_ENDPOINT("/v1/markets/options/lookup")
{
	// whadduhya got whadduhya got
}


//
// OptionsData Destructor
//

OptionsData::~OptionsData () {}


//
// Retrieve Option Chain for a fixed (symbol, expiry) pair
// https://documentation.tradier.com/brokerage-api/markets/get-options-chains
//

nlohmann::json OptionsData::getChain(const std::string& symbol, const std::string& expiry, const bool greekAndVol) const {
	std::string endpoint = OPTIONS_CHAINS_ENDPOINT + "?symbol=" + symbol
												   + "&expiration=" + expiry
												   + "&greeks=" + std::to_string(greekAndVol);
	try {
		auto response = sendGetRequest(endpoint);
		return response["options"]["option"];
	} catch (std::exception& e) {
		std::cerr << "Option Expiration getChain GET no good: " << e.what() << std::endl;
		return nlohmann::json();
	}

	return nlohmann::json();
}


//
// Get an options strike prices for a specified underlying ticker symbol (and contract expiration date?).
// https://documentation.tradier.com/brokerage-api/markets/get-options-strikes
//

nlohmann::json OptionsData::getStrikesForExpiry(const std::string& symbol, const std::string& expiry, const bool includeAllRoots) const {
	std::string endpoint = OPTIONS_STRIKES_ENDPOINT + "?symbol=" + symbol
													+ "&expiration=" + expiry
													+ "&includeAllRoots=" + std::to_string(includeAllRoots);

	try {
		auto response = sendGetRequest(endpoint);
		return response["strikes"]["strike"];
	} catch (std::exception& e) {
		std::cerr << "Option strike GET request no good: " << e.what() << std::endl;
		return nlohmann::json();
	}

	return nlohmann::json();
}


//
// Get Specs About Options Contracts
// Ex: {"contract_size":100,"date":"2024-06-28","expiration_type":"quarterlys"}
//

nlohmann::json OptionsData::getOptionsContracts(const std::string& symbol, bool strikePrice, bool contractSize, bool expiryFreq) const {
	std::string endpoint = OPTIONS_EXPIRIES_ENDPOINT + "?symbol=" + symbol
													 + "&strikePrice=" + std::to_string(strikePrice)
													 + "&contractSize=" + std::to_string(contractSize)
													 + "&expirationType=" + std::to_string(expiryFreq);
	try {
		auto response = sendGetRequest(endpoint);
		return response["expirations"]["expiration"];
	} catch (std::exception& e) {
		std::cerr << "Option expiration GET no good: " << e.what() << std::endl;
		return nlohmann::json();
	}
	return nlohmann::json();
}


//
// Retrieve All Listed Options Clearning Corp (OCC) Symbols for Stock
// https://documentation.tradier.com/brokerage-api/markets/get-lookup-options-symbols
//

nlohmann::json OptionsData::getOccsFromUnderlying(const std::string& symbol) const {
	std::string endpoint = OPTIONS_LOOKUP_ENDPOINT + "?underlying=" + symbol;
	try {
		auto response = sendGetRequest(endpoint);
		return response["symbols"];
	} catch (std::exception& e) {
		std::cerr << "Option symbol lookup no good: " << e.what() << std::endl;
		return nlohmann::json();
	}
	return nlohmann::json();
}
// FILE: `src/EquitiesData.cpp`
#include <iostream>
#include "EquitiesData.h"

EquitiesData::EquitiesData(const std::string& accountNumber, const std::string& authToken, bool liveTrade) : Tradier(accountNumber, authToken, liveTrade), QUOTES_ENDPOINT("/v1/markets/quotes"), QUOTES_HISTORICAL_ENDPOINT("/v1/markets/history") {
	// move along, nothing to see here.
}

EquitiesData::~EquitiesData() {}

nlohmann::json EquitiesData::getQuotes(const std::string& symbols) const {
	std::string endpoint = QUOTES_ENDPOINT + "?symbols=" + symbols;
	try {
		auto response = sendGetRequest(endpoint);
		return response["quotes"]["quote"];
	} catch (std::exception& e) {
		std::cerr << "Quote GET request no good: " << e.what() << std::endl;
		return nlohmann::json();
	}
}


nlohmann::json EquitiesData::getHistoricalQuotes(const std::string& symbol, const std::string& timeInterval, const std::string& startDate, const std::string& endDate, const std::string& sessionFilter) const {
	std::string endpoint = QUOTES_HISTORICAL_ENDPOINT + "?symbol=" + symbol
													  + "&interval=" + timeInterval
													  + "&start=" + startDate
													  + "&end=" + endDate
													  + "&session_filter=" + sessionFilter;

	try {
		auto response = sendGetRequest(endpoint);

		if (response.contains("history") && response["history"].contains("day")) {
			return response["history"]["day"];
		} else {
			std::cerr << "Historical quotes not found in response [getHistoricalQuotes]" << std::endl;
			return nlohmann::json();
		}
		return response;
	} catch (std::exception& e) {
		std::cerr << "HistoricalQuotes GET no good: " << e.what() << std::endl;
		return nlohmann::json();
	}
	return nlohmann::json();
}


//
// SAMPLE RETURNED `response` WHEN CALLED FROM MAIN
// • Note - this is basically what you find in Tradier's Historical Quotes Docs
//

// {
//     "history": {
//         "day": [
//             {
//                 "close": 169.3,
//                 "date": "2024-05-01",
//                 "high": 172.705,
//                 "low": 169.11,
//                 "open": 169.58,
//                 "volume": 50383147
//             },
//             {
//                 "close": 173.03,
//                 "date": "2024-05-02",
//                 "high": 173.415,
//                 "low": 170.89,
//                 "open": 172.51,
//                 "volume": 94214915
//             },
//             {
//                 "close": 183.38,
//                 "date": "2024-05-03",
//                 "high": 187.0,
//                 "low": 182.66,
//                 "open": 186.645,
//                 "volume": 163224110
//             },
//             {
//                 "close": 181.71,
//                 "date": "2024-05-06",
//                 "high": 184.2,
//                 "low": 180.42,
//                 "open": 182.354,
//                 "volume": 78569667
//             },
//             {
//                 "close": 182.4,
//                 "date": "2024-05-07",
//                 "high": 184.9,
//                 "low": 181.32,
//                 "open": 183.45,
//                 "volume": 77305771
//             },
//             {
//                 "close": 182.74,
//                 "date": "2024-05-08",
//                 "high": 183.07,
//                 "low": 181.45,
//                 "open": 182.85,
//                 "volume": 45057087
//             },
//             {
//                 "close": 184.57,
//                 "date": "2024-05-09",
//                 "high": 184.66,
//                 "low": 182.11,
//                 "open": 182.56,
//                 "volume": 48982972
//             },
//             {
//                 "close": 183.05,
//                 "date": "2024-05-10",
//                 "high": 185.09,
//                 "low": 182.13,
//                 "open": 184.9,
//                 "volume": 50759496
//             },
//             {
//                 "close": 186.28,
//                 "date": "2024-05-13",
//                 "high": 187.1,
//                 "low": 184.62,
//                 "open": 185.435,
//                 "volume": 72044809
//             },
//             {
//                 "close": 187.43,
//                 "date": "2024-05-14",
//                 "high": 188.3,
//                 "low": 186.29,
//                 "open": 187.51,
//                 "volume": 52393619
//             },
//             {
//                 "close": 189.72,
//                 "date": "2024-05-15",
//                 "high": 190.65,
//                 "low": 187.37,
//                 "open": 187.91,
//                 "volume": 70399988
//             },
//             {
//                 "close": 189.84,
//                 "date": "2024-05-16",
//                 "high": 191.095,
//                 "low": 189.6601,
//                 "open": 190.47,
//                 "volume": 52845230
//             },
//             {
//                 "close": 189.87,
//                 "date": "2024-05-17",
//                 "high": 190.81,
//                 "low": 189.18,
//                 "open": 189.51,
//                 "volume": 41282925
//             },
//             {
//                 "close": 191.04,
//                 "date": "2024-05-20",
//                 "high": 191.9199,
//                 "low": 189.01,
//                 "open": 189.325,
//                 "volume": 44361275
//             },
//             {
//                 "close": 192.35,
//                 "date": "2024-05-21",
//                 "high": 192.73,
//                 "low": 190.9201,
//                 "open": 191.09,
//                 "volume": 42309401
//             },
//             {
//                 "close": 190.9,
//                 "date": "2024-05-22",
//                 "high": 192.8231,
//                 "low": 190.27,
//                 "open": 192.265,
//                 "volume": 34648547
//             },
//             {
//                 "close": 186.88,
//                 "date": "2024-05-23",
//                 "high": 191.0,
//                 "low": 186.625,
//                 "open": 190.98,
//                 "volume": 51005924
//             },
//             {
//                 "close": 189.98,
//                 "date": "2024-05-24",
//                 "high": 190.58,
//                 "low": 188.0404,
//                 "open": 188.82,
//                 "volume": 36326975
//             },
//             {
//                 "close": 189.99,
//                 "date": "2024-05-28",
//                 "high": 193.0,
//                 "low": 189.1,
//                 "open": 191.51,
//                 "volume": 52280051
//             },
//             {
//                 "close": 190.29,
//                 "date": "2024-05-29",
//                 "high": 192.247,
//                 "low": 189.51,
//                 "open": 189.61,
//                 "volume": 53068016
//             },
//             {
//                 "close": 191.29,
//                 "date": "2024-05-30",
//                 "high": 192.18,
//                 "low": 190.63,
//                 "open": 190.76,
//                 "volume": 49947941
//             },
//             {
//                 "close": 192.25,
//                 "date": "2024-05-31",
//                 "high": 192.57,
//                 "low": 189.91,
//                 "open": 191.44,
//                 "volume": 75158277
//             }
//         ]
//     }
// }
// FILE: `include/Tradier.h`
#ifndef TRADIER_H
#define TRADIER_H

#include <string>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class Tradier {
public:
	Tradier(const std::string& accountNumber, const std::string& authToken, bool liveTrade=false);
	virtual ~Tradier();

	// nlohmann::json startMarketSession() const;

protected:
	std::string ACCOUNT_NUMBER;
	std::string AUTH_TOKEN;
	std::map<std::string, std::string> API_HEADERS;

	std::string LIVETRADE_URL;
	std::string SANDBOX_URL;
	std::string MARKET_STREAM_URL;
	std::string BASE_URL;

	static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* s);
	nlohmann::json sendRequest(const std::string& endpoint, const std::string& method, const std::string& postData="") const;
	nlohmann::json sendGetRequest(const std::string& endpoint) const;
	nlohmann::json sendPostRequest(const std::string& endpoint, const std::string& postData) const;
};

#endif
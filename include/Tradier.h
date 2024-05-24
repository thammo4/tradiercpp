// FILE: `include/Tradier.h`
#ifndef TRADIER_H
#define TRADIER_H

#include <string>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>


namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

class Tradier {
public:
	Tradier(const std::string& accountNumber, const std::string& authToken, bool liveTrade=false);
	virtual ~Tradier();

	nlohmann::json startMarketSession() const;
	void startWebSocket(const std::string& sessionId) const;

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
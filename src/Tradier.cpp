// FILE: `src/Tradier.cpp`
#include "Tradier.h"
#include <iostream>

Tradier::Tradier(const std::string& accountNumber, const std::string& authToken, bool liveTrade)
	: ACCOUNT_NUMBER(accountNumber),
	  AUTH_TOKEN(authToken),
	  LIVETRADE_URL("https://api.tradier.com"),
	  SANDBOX_URL("https://sandbox.tradier.com"),
	  MARKET_STREAM_URL("wss://ws.tradier.com"),
	  API_HEADERS({
	  	{"Authorization", "Bearer " + authToken},
	  	{"Accept", "application/json"}
	  }),
	  BASE_URL(liveTrade ? "https://api.tradier.com" : "https://sandbox.tradier.com")
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

Tradier::~Tradier() {
	curl_global_cleanup();
}

size_t Tradier::writeCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
	size_t newLength = size*nmemb;
	s->append((char*)contents, newLength);
	return newLength;
}


//
// GET Request Call
//

nlohmann::json Tradier::sendGetRequest(const std::string& endpoint) const {
	return sendRequest(endpoint, "GET");
}


//
// POST Request Call
//

nlohmann::json Tradier::sendPostRequest(const std::string& endpoint, const std::string& postData) const {
	return sendRequest(endpoint, "POST", postData);
}


//
// Base API HTTP Request Function
//

nlohmann::json Tradier::sendRequest(const std::string& endpoint, const std::string& method, const std::string& postData) const {
	CURL* curl = curl_easy_init();
	std::string readBuffer;
	nlohmann::json jsonResult;
	struct curl_slist* headers = nullptr;

	//
	// Convert the map to curl_slist or else compiler will freak out
	//

	if (curl) {
		for (const auto& header : API_HEADERS) {
			std::string headerValue = header.first + ":" + header.second;
			headers = curl_slist_append(headers, headerValue.c_str());
		}

		std::string fullURL = BASE_URL + endpoint;

		curl_easy_setopt(curl, CURLOPT_URL, fullURL.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		if (method == "POST") {
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			const char* payload = postData.empty() ? "{}" : postData.c_str();
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
		} else if (method == "GET") {
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		}

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "curl failed " << curl_easy_strerror(res) << std::endl;
		}

		curl_easy_cleanup(curl);
	}

	try {
		jsonResult = nlohmann::json::parse(readBuffer);
		if (jsonResult.is_null()) {
			std::cerr << "no api data" << std::endl;
		}
	} catch (nlohmann::json::exception& e) {
		std::cerr << "JSON PARSE ERROR " << e.what() << std::endl;
	}

	return jsonResult;
}
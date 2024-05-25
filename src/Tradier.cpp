// FILE: `src/Tradier.cpp`
#include "Tradier.h"
#include <iostream>
#include <fstream>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>


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
		std::cout << "URL: " << fullURL << std::endl;

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

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	} else {
		std::cerr << "Failed CURL initialization." << std::endl;
	}

	try {
		jsonResult = nlohmann::json::parse(readBuffer);
		if (jsonResult.is_null()) {
			std::cerr << "no api data" << std::endl;
		}
	} catch (nlohmann::json::exception& e) {
		std::cerr << "JSON PARSE ERROR " << e.what() << std::endl;
		return nlohmann::json();
	}

	return jsonResult;
}



//
// WebSocket Streaming Connection
//

void Tradier::startWebSocket(const std::string& sessionId) const {
	std::cout << "START startWebSocket" << std::endl;
	boost::asio::io_context ioc;
	boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tlsv12_client);
	std::cout << "Calls to boost_asio_io and boost_asio_ssl ok" << std::endl;
	ssl_context.set_default_verify_paths();

	try {
		//
		// Create WebSocket Stream
		//

		tcp::resolver resolver{ioc};
		auto const results = resolver.resolve("ws.tradier.com", "443");

		//
		// SSL Connection
		//

		using ssl_stream = boost::asio::ssl::stream<tcp::socket>;
		websocket::stream<ssl_stream> ws(ioc, ssl_context);

		//
		// Establish TCP Connection
		//

		boost::asio::connect(ws.next_layer().next_layer(), results.begin(), results.end());

		//
		// SSL Handshake
		//

		ws.next_layer().handshake(boost::asio::ssl::stream_base::client);
		ws.handshake("ws.tradier.com", "/v1/markets/events");

		//
		// Configure Payload Parameters
		//

		std::string payload = R"({"sessionid": ")" + sessionId + R"(",)"
			R"("symbols": ["AMZN", "AXP", "AMGN", "AAPL", "BA", "CAT", "CSCO", "CVX", "GS", "HD", "HON", "IBM", "INTC", "JNJ", "KO", "JPM", "MCD", "MMM", "MRK", "MSFT", "NKE", "PG", "TRV", "UNH", "CRM", "VZ", "V", "WMT", "DIS", "DOW"],)"
			R"("linebreak":false})";

		//
		// Send Payload
		//

		ws.write(boost::asio::buffer(payload));
		std::cout << ">>> " << payload << std::endl;

		//
		// Read Response from Buffer
		//

		std::ofstream outputFile("market_data.txt", std::ios_base::app);
		boost::beast::flat_buffer buffer;

		while (true) {
			ws.read(buffer);
			auto msg = boost::beast::buffers_to_string(buffer.data());
			// std::cout << "<<< " << msg << std::endl;
			outputFile << msg << std::endl;
			buffer.consume(buffer.size());
		}

		//
		// Close up Shop
		//

		ws.close(websocket::close_code::normal);


	//
	// Handle All Kind of Errors
	//

	} catch (const boost::system::system_error& e) {
		std::cerr << "System error websocket: " << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "ugh!" << std::endl;
	}
}
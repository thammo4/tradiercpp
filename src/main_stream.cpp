// FILE: `src/main_stream.cpp`
#include "Tradier.h"
#include "EnvReader.h"
#include <iostream>
#include <string>

int main() {
	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct_live"];
	std::string authToken = env["tradier_token_live"];
	bool liveTrade = true;

	Tradier tradier(accountNumber, authToken, liveTrade);

	auto sessionResponse = tradier.startMarketSession();
	std::string sessionId = sessionResponse["stream"]["sessionid"].get<std::string>();

	tradier.startWebSocket(sessionId);

	return 0;
}
// FILE: `src/main_dataprocess.cpp`
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

void processStreamData(const std::string& rawMarketData) {
	auto json = nlohmann::json::parse(rawMarketData);
	std::cout << "Processed JSON: " << json.dump(4) << std::endl;
}


int main() {
	std::ifstream inputStream("market_data.txt");
	std::string line;

	while (getline(inputStream, line)) {
		processStreamData(line);
	}
	inputStream.close();

	return 0;
}
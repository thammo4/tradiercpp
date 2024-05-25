// FILE: `src/main_dataprocess.cpp`
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

void processStreamData(const std::string& rawMarketData, std::ofstream& outputFile) {
	try {
		auto json = nlohmann::json::parse(rawMarketData);
		outputFile << json.dump(4) << std::endl;
		std::cout << "Processed JSON: " << json.dump(4) << std::endl;
	} catch (const nlohmann::json::parse_error& e) {
		std::cerr << "JSON issue: " << e.what() << std::endl;
	}
}


int main() {
	std::ifstream inputStream("market_data.txt");
	std::ofstream outputFile("processed_data.json", std::ios::app);
	std::string line;

	if (! inputStream.is_open()) {
		std::cerr << "Failed to open market data file" << std::endl;
		return -1;
	}

	if (! outputFile.is_open()) {
		std::cerr << "Failed to open json file" << std::endl;
		return -1;
	}

	while (getline(inputStream, line)) {
		processStreamData(line, outputFile);
	}

	inputStream.close();
	outputFile.close();

	return 0;
}
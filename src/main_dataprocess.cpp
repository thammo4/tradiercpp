// FILE: `src/main_dataprocess.cpp`
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
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

//
// Date function to format the output JSON file
//

std::string dateToday() {
	auto now = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(now);

	std::tm buff;
	localtime_r(&time_t, &buff);

	std::ostringstream ss;
	ss << std::put_time(&buff, "%B%d");

	return ss.str();
}


int main() {
	std::string outputFilename = "../data/processed_" + dateToday() + ".json";
	std::ifstream inputStream("../data/market_data.txt");
	std::ofstream outputFile(outputFilename, std::ios::app);

	if (! inputStream.is_open()) {
		std::cerr << "Failed to open market data file" << std::endl;
		return -1;
	}

	if (! outputFile.is_open()) {
		std::cerr << "Failed to open json file" << std::endl;
		return -1;
	}

	std::string line;
	while (getline(inputStream, line)) {
		processStreamData(line, outputFile);
	}

	inputStream.close();
	outputFile.close();

	return 0;
}
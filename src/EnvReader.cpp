// FILE: `src/EnvReader.cpp`
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "EnvReader.h"


std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\r\n");
	if (first == std::string::npos) return "";
	size_t last = str.find_last_not_of(" \t\r\n");
	return str.substr(first, (last-first+1));
}

std::map<std::string, std::string> loadEnv(const std::string& filename) {
	std::map<std::string, std::string> env;
	std::ifstream file(filename);
	std::string line;

	if (! file) {
		std::cerr << "Cant open file cmon " << filename << std::endl;
		return env;
	}

	while (getline(file, line)) {
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '=')) {
			std::string value;
			if (std::getline(is_line, value)) {
				// env[key] = value;
				key = trim(key);
				value = trim(value);
				env[key] = value;
			}
		}
	}

	file.close();
	return env;
}
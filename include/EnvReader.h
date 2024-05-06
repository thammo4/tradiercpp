// FILE `include/EnvReader.h`
#ifndef ENVREADER_H
#define ENVREADER_H

#include <string>
#include <map>

std::string trim(const std::string& str);
std::map<std::string, std::string> loadEnv(const std::string& filename);

#endif
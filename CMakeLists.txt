cmake_minimum_required(VERSION 3.10)

project(TradierCPP VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(/opt/homebrew/Cellar/nlohmann-json/3.11.3/include)

add_executable(TradierCPP src/Tradier.cpp src/Account.cpp src/EnvReader.cpp src/main.cpp)

find_package(CURL REQUIRED)

if (CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	target_link_libraries(TradierCPP ${CURL_LIBRARIES})
endif()
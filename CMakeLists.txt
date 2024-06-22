cmake_minimum_required(VERSION 3.10)
project(TradierCPP VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# Include Directories
#

include_directories(include /opt/homebrew/Cellar/nlohmann-json/3.11.3/include)

#
# Find Required Packages
#

find_package(CURL REQUIRED)
find_package(Boost 1.85.0 REQUIRED COMPONENTS system thread coroutine context)
find_package(OpenSSL REQUIRED)


#
# Define Common Source Files
#

set(COMMON_SRC
	src/Tradier.cpp
	src/Account.cpp
	src/EnvReader.cpp
	src/TradierHTTPConnect.cpp
	src/EquityOrder.cpp
	src/OptionsOrder.cpp
	src/EquitiesData.cpp
	src/OptionsData.cpp
)


#
# Define Executable - WebSocket Streaming
#

add_executable(TradierStream src/main_stream.cpp ${COMMON_SRC})
target_include_directories(TradierStream PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(TradierStream PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL)
target_link_libraries(TradierStream PRIVATE Boost::system Boost::thread Boost::coroutine Boost::context)



#
# Define Executable - Data Processing
#

add_executable(TradierDataProcess src/main_dataprocess.cpp ${COMMON_SRC})
target_include_directories(TradierDataProcess PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(TradierDataProcess PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL)
target_link_libraries(TradierDataProcess PRIVATE Boost::system Boost::thread Boost::coroutine Boost::context)


#
# Define Executable - Generic Main
#

add_executable(TradierCPP src/main.cpp ${COMMON_SRC})
target_include_directories(TradierCPP PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(TradierCPP PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL)
target_link_libraries(TradierCPP PRIVATE Boost::system Boost::thread Boost::coroutine Boost::context)
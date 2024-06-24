# FILE: `CMakeLists.txt`

cmake_minimum_required(VERSION 3.12)
project(TradierCPP VERSION 1.0)

#
# Uncomment the following two lines for verbose build
#

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")


# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# Include Directories
#

include_directories(include
	/opt/homebrew/Cellar/nlohmann-json/3.11.3/include
	/opt/homebrew/Cellar/quantlib/1.34/include
	lib/DataFrame/include
)

#
# Find Required Packages
#

find_package(CURL REQUIRED)
find_package(Boost 1.85.0 REQUIRED COMPONENTS system thread coroutine context math_c99)
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
# Define Executable - QuantLib Integration Example
#

add_executable(PANWExample src/main_panwEX.cpp ${COMMON_SRC})
target_include_directories(PANWExample PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} /opt/homebrew/Cellar/quantlib/1.34/include)
target_link_libraries(PANWExample PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL Boost::system Boost::thread Boost::coroutine Boost::context Boost::math_c99 /opt/homebrew/Cellar/quantlib/1.34/lib/libQuantLib.dylib)


#
# Define Executable - QuantLib/TradierCPP Black-Scholes Options Pricing Model
#

add_executable(TradierQLib src/main_tradierqlib.cpp ${COMMON_SRC})
target_include_directories(TradierQLib PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} /opt/homebrew/Cellar/quantlib/1.34/include)
target_link_libraries(TradierQLib PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL Boost::system Boost::thread Boost::coroutine Boost::context Boost::math_c99 /opt/homebrew/Cellar/quantlib/1.34/lib/libQuantLib.dylib)

#
# Define Executable - Generic Main
#

add_executable(TradierCPP src/main.cpp ${COMMON_SRC})
target_include_directories(TradierCPP PRIVATE ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(TradierCPP PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL)
target_link_libraries(TradierCPP PRIVATE Boost::system Boost::thread Boost::coroutine Boost::context)

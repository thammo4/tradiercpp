cmake_minimum_required(VERSION 3.10)
project(TradierCPP VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add Executable
add_executable(TradierCPP src/Tradier.cpp src/Account.cpp src/EnvReader.cpp src/TradierHTTPConnect.cpp src/main.cpp)


#
# Find Required Packages
#

find_package(CURL REQUIRED)
find_package(Boost 1.85.0 REQUIRED COMPONENTS system thread coroutine context)
find_package(OpenSSL REQUIRED)

#
# Include Directories + Link Libraries
#

target_include_directories(TradierCPP PRIVATE include /opt/homebrew/Cellar/nlohmann-json/3.11.3/include ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(TradierCPP PRIVATE ${CURL_LIBRARIES} ${Boost_LIBRARIES} OpenSSL::SSL)

target_link_libraries(TradierCPP PRIVATE Boost::system Boost::thread Boost::coroutine Boost::context)
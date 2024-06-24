// FILE: `src/main_panwEX.cpp`
#include "EnvReader.h"
#include "EquitiesData.h"
#include "OptionsData.h"
#include "OptionsOrder.h"
#include "Tradier.h"

#include <iostream>
#include <ql/quantlib.hpp>

// #include "DataFrame/DataFrame.h"


int main() {

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	EquitiesData equitiesData(accountNumber, authToken, liveTrade);
	OptionsData optionsData(accountNumber, authToken, liveTrade);
	OptionsOrder optionsOrder(accountNumber, authToken, liveTrade);

	auto panwQuote = equitiesData.getQuotes("PANW");
	auto panwOptionsExpiries = optionsData.getOptionsContracts("PANW", true, true, true);

	auto panwChainJun28 = optionsData.getChain("PANW", "2024-06-28");
	auto panwChainNov15 = optionsData.getChain("PANW", "2024-11-15");

	auto panwStrikesJun28 = optionsData.getStrikesForExpiry("PANW", "2024-06-28");
	auto panwStrikesNov15 = optionsData.getStrikesForExpiry("PANW", "2024-11-15");

	auto panwOccs = optionsData.getOccsFromUnderlying("PANW");

	QuantLib::Date today = QuantLib::Date::todaysDate();
	std::cout << "hello, TradierQLib!" << std::endl;
	std::cout << "QuantLib says that today is: " << today << std::endl;
	std::cout << std::endl;

	std::cout << "Palo Alto Networks Market Data" << std::endl;
	std::cout << std::endl;

	std::cout << "Current Quote" << std::endl;
	std::cout << panwQuote << std::endl;
	std::cout << std::endl;

	std::cout << "Options Expirations" << std::endl;
	std::cout << panwOptionsExpiries << std::endl;
	std::cout << std::endl;

	std::cout << "Options Strikes [Jun 28]" << std::endl;
	std::cout << panwStrikesJun28 << std::endl;
	std::cout << std::endl;

	std::cout << "Options Chain [Jun 28]" << std::endl;
	std::cout << panwChainJun28 << std::endl;
	std::cout << std::endl;

	std::cout << panwChainJun28.dump(4) << std::endl;
	std::cout << std::endl;

	return 0;
}


//
// OUTPUT
//

// thammons@toms-MacBook-Air build % make
// [ 20%] Built target TradierStream
// [ 40%] Built target TradierDataProcess
// [ 42%] Building CXX object CMakeFiles/PANWExample.dir/src/main_panwEX.cpp.o
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/src/main_panwEX.cpp:11:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrame.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameStatsVisitors.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameTypes.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/HeteroVector.h:33:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/HeteroConstPtrView.h:32:
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorPtrView.h:357:23: error: no type named 'semiregular' in namespace 'std'
//         template<std::semiregular I>
//                  ~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorPtrView.h:358:37: error: unknown type name 'I'
//         inline iterator operator - (I step) const noexcept  {
//                                     ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorPtrView.h:545:23: error: no type named 'semiregular' in namespace 'std'
//         template<std::semiregular I>
//                  ~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorPtrView.h:546:43: error: unknown type name 'I'
//         inline const_iterator operator - (I step) const noexcept  {
//                                           ^
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/src/main_panwEX.cpp:11:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrame.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameStatsVisitors.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameTypes.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/HeteroVector.h:34:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/HeteroConstView.h:32:
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:303:23: error: no type named 'semiregular' in namespace 'std'
//         template<std::semiregular I>
//                  ~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:304:43: error: unknown type name 'I'
//         inline const_iterator operator - (I step) const noexcept  {
//                                           ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:453:23: error: no type named 'semiregular' in namespace 'std'
//         template<std::semiregular I>
//                  ~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:454:37: error: unknown type name 'I'
//         inline iterator operator - (I step) const noexcept  {
//                                     ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:751:23: error: no type named 'semiregular' in namespace 'std'
//         template<std::semiregular I>
//                  ~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Vectors/VectorView.h:752:43: error: unknown type name 'I'
//         inline const_iterator operator - (I step) const noexcept  {
//                                           ^
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/src/main_panwEX.cpp:11:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrame.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameStatsVisitors.h:33:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Internals/DataFrame_standalone.tcc:33:
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:177:19: error: no member named 'endian' in namespace 'std'; did you mean 'endians'?
//     if constexpr (std::endian::native == std::endian::big)
//                   ^~~~~~~~~~~
//                   endians
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:43:13: note: 'endians' declared here
// enum class  endians : unsigned char  {
//             ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:177:42: error: no member named 'endian' in namespace 'std'; did you mean 'endians'?
//     if constexpr (std::endian::native == std::endian::big)
//                                          ^~~~~~~~~~~
//                                          endians
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:43:13: note: 'endians' declared here
// enum class  endians : unsigned char  {
//             ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:177:32: error: no member named 'native' in 'hmdf::endians'
//     if constexpr (std::endian::native == std::endian::big)
//                   ~~~~~~~~~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:177:55: error: no member named 'big' in 'hmdf::endians'
//     if constexpr (std::endian::native == std::endian::big)
//                                          ~~~~~~~~~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:179:24: error: no member named 'endian' in namespace 'std'; did you mean 'endians'?
//     else if constexpr (std::endian::native == std::endian::little)
//                        ^~~~~~~~~~~
//                        endians
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:43:13: note: 'endians' declared here
// enum class  endians : unsigned char  {
//             ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:179:47: error: no member named 'endian' in namespace 'std'; did you mean 'endians'?
//     else if constexpr (std::endian::native == std::endian::little)
//                                               ^~~~~~~~~~~
//                                               endians
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:43:13: note: 'endians' declared here
// enum class  endians : unsigned char  {
//             ^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:179:37: error: no member named 'native' in 'hmdf::endians'
//     else if constexpr (std::endian::native == std::endian::little)
//                        ~~~~~~~~~~~~~^
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Endianness.h:179:60: error: no member named 'little' in 'hmdf::endians'
//     else if constexpr (std::endian::native == std::endian::little)
//                                               ~~~~~~~~~~~~~^
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/src/main_panwEX.cpp:11:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrame.h:32:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/DataFrameStatsVisitors.h:33:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Internals/DataFrame_standalone.tcc:34:
// In file included from /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Threads/ThreadGranularity.h:32:
// /Users/thammons/Desktop/msds/Tradier/tradiercpp/lib/DataFrame/include/DataFrame/Utils/Threads/ThreadPool.h:76:5: error: unknown type name 'requires'
//     requires std::invocable<F, As ...>
//     ^
// fatal error: too many errors emitted, stopping now [-ferror-limit=]
// 20 errors generated.
// make[2]: *** [CMakeFiles/PANWExample.dir/src/main_panwEX.cpp.o] Error 1
// make[1]: *** [CMakeFiles/PANWExample.dir/all] Error 2
// make: *** [all] Error 2
// thammons@toms-MacBook-Air build % 

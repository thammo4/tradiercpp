// FILE: `src/main_tradierqlib.cpp`
#include "EnvReader.h"
#include "EquitiesData.h"
#include "OptionsData.h"
#include "OptionsOrder.h"
#include "Tradier.h"

#include <iostream>
#include <ql/quantlib.hpp>


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

	std::cout << "Options Strikes [Nov 15]" << std::endl;
	std::cout << panwStrikesJun28 << std::endl;
	std::cout << std::endl;

	std::cout << "Options Chain [Nov 15]" << std::endl;
	std::cout << panwChainNov15 << std::endl;
	std::cout << std::endl;

	std::cout << "Options Clearing Corp Symbols (OCC)" << std::endl;
	std::cout << panwOccs << std::endl;
	std::cout << std::endl;

	return 0;
}


//
// OUTPUT
//

// thammons@toms-MacBook-Air build % ./TradierQLib
// hello, TradierQLib!
// QuantLib says that today is: June 24th, 2024
//
// Palo Alto Networks Market Data
//
// Current Quote
// {"ask":316.42,"ask_date":1719254143000,"askexch":"M","asksize":2,"average_volume":1199117,"bid":316.25,"bid_date":1719254125000,"bidexch":"Q","bidsize":2,"change":-4.0,"change_percentage":-1.25,"close":null,"description":"Palo Alto Networks Inc","exch":"Q","high":326.8,"last":316.335,"last_volume":200,"low":316.25,"open":318.74,"prevclose":320.33,"root_symbols":"PANW","symbol":"PANW","trade_date":1719254143472,"type":"stock","volume":2135024,"week_52_high":380.84,"week_52_low":201.17}
//
// Options Expirations
// [{"contract_size":100,"date":"2024-06-28","expiration_type":"quarterlys"},{"contract_size":100,"date":"2024-07-05","expiration_type":"weeklys"},{"contract_size":100,"date":"2024-07-12","expiration_type":"weeklys"},{"contract_size":100,"date":"2024-07-19","expiration_type":"standard"},{"contract_size":100,"date":"2024-07-26","expiration_type":"weeklys"},{"contract_size":100,"date":"2024-08-02","expiration_type":"weeklys"},{"contract_size":100,"date":"2024-08-16","expiration_type":"standard"},{"contract_size":100,"date":"2024-09-20","expiration_type":"standard"},{"contract_size":100,"date":"2024-11-15","expiration_type":"standard"},{"contract_size":100,"date":"2024-12-20","expiration_type":"standard"},{"contract_size":100,"date":"2025-01-17","expiration_type":"standard"},{"contract_size":100,"date":"2025-03-21","expiration_type":"standard"},{"contract_size":100,"date":"2025-06-20","expiration_type":"standard"},{"contract_size":100,"date":"2025-09-19","expiration_type":"standard"},{"contract_size":100,"date":"2026-01-16","expiration_type":"standard"}]
//
// Options Strikes [Jun 28]
// [150.0,155.0,160.0,165.0,170.0,175.0,180.0,185.0,190.0,195.0,200.0,205.0,210.0,215.0,220.0,225.0,230.0,235.0,240.0,245.0,250.0,255.0,260.0,265.0,270.0,275.0,277.5,280.0,282.5,285.0,287.5,290.0,292.5,295.0,297.5,300.0,302.5,305.0,307.5,310.0,312.5,315.0,317.5,320.0,322.5,325.0,327.5,330.0,332.5,335.0,337.5,340.0,342.5,345.0,350.0,355.0,360.0,365.0,370.0,375.0,380.0,385.0,390.0,395.0,400.0,405.0,410.0,415.0,420.0,425.0,430.0,440.0,450.0,460.0,470.0,480.0,490.0]
//
// Options Chain [Jun 28]
// [{"ask":{"0":0.01,"1":171.0,"2":8.05,"3":166.0,"4":4.3,"5":161.05,"6":8.05,"7":156.05,"8":4.3,"9":151.05},"ask_date":{"0":1719235811000,"1":1719254010000,"2":1719235801000,"3":1719254010000,"4":1719235805000,"5":1719254010000,"6":1719235801000,"7":1719254010000,"8":1719235805000,"9":1719254010000},"askexch":{"0":"U","1":"N","2":"D","3":"N","4":"C","5":"N","6":"D","7":"N","8":"C","9":"N"},"asksize":{"0":35,"1":41,"2":1,"3":41,"4":9,"5":41,"6":1,"7":41,"8":8,"9":41},"average_volume":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"bid":{"0":0.0,"1":165.75,"2":0.0,"3":160.6,"4":0.0,"5":155.75,"6":0.0,"7":150.75,"8":0.0,"9":145.8},"bid_date":{"0":1719230400000,"1":1719249731000,"2":1719230400000,"3":1719253817000,"4":1719230400000,"5":1719249731000,"6":1719230400000,"7":1719249731000,"8":1719230400000,"9":1719250562000},"bidexch":{"0":null,"1":"Z","2":null,"3":"Z","4":null,"5":"Z","6":null,"7":"Z","8":null,"9":"Z"},"bidsize":{"0":0,"1":41,"2":0,"3":53,"4":0,"5":41,"6":0,"7":41,"8":0,"9":41},"change":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":0.0,"6":null,"7":null,"8":0.0,"9":null},"change_percentage":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":0.0,"6":null,"7":null,"8":0.0,"9":null},"close":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"contract_size":{"0":100,"1":100,"2":100,"3":100,"4":100,"5":100,"6":100,"7":100,"8":100,"9":100},"description":{"0":"PANW Jun 28 2024 $150.00 Put","1":"PANW Jun 28 2024 $150.00 Call","2":"PANW Jun 28 2024 $155.00 Put","3":"PANW Jun 28 2024 $155.00 Call","4":"PANW Jun 28 2024 $160.00 Put","5":"PANW Jun 28 2024 $160.00 Call","6":"PANW Jun 28 2024 $165.00 Put","7":"PANW Jun 28 2024 $165.00 Call","8":"PANW Jun 28 2024 $170.00 Put","9":"PANW Jun 28 2024 $170.00 Call"},"exch":{"0":"Z","1":"Z","2":"Z","3":"Z","4":"Z","5":"Z","6":"Z","7":"Z","8":"Z","9":"Z"},"expiration_date":{"0":"2024-06-28","1":"2024-06-28","2":"2024-06-28","3":"2024-06-28","4":"2024-06-28","5":"2024-06-28","6":"2024-06-28","7":"2024-06-28","8":"2024-06-28","9":"2024-06-28"},"expiration_type":{"0":"quarterlys","1":"quarterlys","2":"quarterlys","3":"quarterlys","4":"quarterlys","5":"quarterlys","6":"quarterlys","7":"quarterlys","8":"quarterlys","9":"quarterlys"},"high":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"last":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":150.25,"6":null,"7":null,"8":1.44,"9":null},"last_volume":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":1,"6":0,"7":0,"8":5,"9":0},"low":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"open":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"open_interest":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":1,"6":0,"7":0,"8":5,"9":0},"option_type":{"0":"put","1":"call","2":"put","3":"call","4":"put","5":"call","6":"put","7":"call","8":"put","9":"call"},"prevclose":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":150.25,"6":null,"7":null,"8":1.44,"9":null},"root_symbol":{"0":"PANW","1":"PANW","2":"PANW","3":"PANW","4":"PANW","5":"PANW","6":"PANW","7":"PANW","8":"PANW","9":"PANW"},"strike":{"0":150.0,"1":150.0,"2":155.0,"3":155.0,"4":160.0,"5":160.0,"6":165.0,"7":165.0,"8":170.0,"9":170.0},"symbol":{"0":"PANW240628P00150000","1":"PANW240628C00150000","2":"PANW240628P00155000","3":"PANW240628C00155000","4":"PANW240628P00160000","5":"PANW240628C00160000","6":"PANW240628P00165000","7":"PANW240628C00165000","8":"PANW240628P00170000","9":"PANW240628C00170000"},"trade_date":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":1716909654234,"6":0,"7":0,"8":1716298254809,"9":0},"type":{"0":"option","1":"option","2":"option","3":"option","4":"option","5":"option","6":"option","7":"option","8":"option","9":"option"},"underlying":{"0":"PANW","1":"PANW","2":"PANW","3":"PANW","4":"PANW","5":"PANW","6":"PANW","7":"PANW","8":"PANW","9":"PANW"},"volume":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"week_52_high":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"week_52_low":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0}}]
//
// Options Strikes [Nov 15]
// [150.0,155.0,160.0,165.0,170.0,175.0,180.0,185.0,190.0,195.0,200.0,205.0,210.0,215.0,220.0,225.0,230.0,235.0,240.0,245.0,250.0,255.0,260.0,265.0,270.0,275.0,277.5,280.0,282.5,285.0,287.5,290.0,292.5,295.0,297.5,300.0,302.5,305.0,307.5,310.0,312.5,315.0,317.5,320.0,322.5,325.0,327.5,330.0,332.5,335.0,337.5,340.0,342.5,345.0,350.0,355.0,360.0,365.0,370.0,375.0,380.0,385.0,390.0,395.0,400.0,405.0,410.0,415.0,420.0,425.0,430.0,440.0,450.0,460.0,470.0,480.0,490.0]
//
// Options Chain [Nov 15]
// [{"ask":{"0":272.0,"1":1.64,"2":1.64,"3":267.2,"4":1.64,"5":262.3,"6":1.64,"7":257.45,"8":1.64,"9":252.55},"ask_date":{"0":1719254069000,"1":1719253436000,"2":1719250824000,"3":1719254011000,"4":1719253384000,"5":1719254010000,"6":1719253384000,"7":1719254010000,"8":1719253384000,"9":1719254010000},"askexch":{"0":"Z","1":"Z","2":"Z","3":"Z","4":"Z","5":"N","6":"Z","7":"N","8":"Z","9":"N"},"asksize":{"0":41,"1":61,"2":61,"3":41,"4":69,"5":41,"6":69,"7":41,"8":69,"9":41},"average_volume":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"bid":{"0":267.0,"1":0.0,"2":0.0,"3":262.15,"4":0.0,"5":256.8,"6":0.0,"7":252.05,"8":0.0,"9":246.65},"bid_date":{"0":1719254010000,"1":1719235803000,"2":1719235803000,"3":1719254010000,"4":1719235803000,"5":1719253437000,"6":1718971200000,"7":1719248149000,"8":1719230400000,"9":1719253520000},"bidexch":{"0":"Z","1":"P","2":"P","3":"Z","4":"P","5":"Z","6":null,"7":"Z","8":null,"9":"Z"},"bidsize":{"0":36,"1":0,"2":0,"3":30,"4":0,"5":53,"6":0,"7":41,"8":0,"9":61},"change":{"0":null,"1":0.0,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"change_percentage":{"0":null,"1":0.0,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"close":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"contract_size":{"0":100,"1":100,"2":100,"3":100,"4":100,"5":100,"6":100,"7":100,"8":100,"9":100},"description":{"0":"PANW Nov 15 2024 $50.00 Call","1":"PANW Nov 15 2024 $50.00 Put","2":"PANW Nov 15 2024 $55.00 Put","3":"PANW Nov 15 2024 $55.00 Call","4":"PANW Nov 15 2024 $60.00 Put","5":"PANW Nov 15 2024 $60.00 Call","6":"PANW Nov 15 2024 $65.00 Put","7":"PANW Nov 15 2024 $65.00 Call","8":"PANW Nov 15 2024 $70.00 Put","9":"PANW Nov 15 2024 $70.00 Call"},"exch":{"0":"Z","1":"Z","2":"Z","3":"Z","4":"Z","5":"Z","6":"Z","7":"Z","8":"Z","9":"Z"},"expiration_date":{"0":"2024-11-15","1":"2024-11-15","2":"2024-11-15","3":"2024-11-15","4":"2024-11-15","5":"2024-11-15","6":"2024-11-15","7":"2024-11-15","8":"2024-11-15","9":"2024-11-15"},"expiration_type":{"0":"standard","1":"standard","2":"standard","3":"standard","4":"standard","5":"standard","6":"standard","7":"standard","8":"standard","9":"standard"},"high":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"last":{"0":null,"1":0.03,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"last_volume":{"0":0,"1":1,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"low":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"open":{"0":null,"1":null,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"open_interest":{"0":0,"1":2,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"option_type":{"0":"call","1":"put","2":"put","3":"call","4":"put","5":"call","6":"put","7":"call","8":"put","9":"call"},"prevclose":{"0":null,"1":0.03,"2":null,"3":null,"4":null,"5":null,"6":null,"7":null,"8":null,"9":null},"root_symbol":{"0":"PANW","1":"PANW","2":"PANW","3":"PANW","4":"PANW","5":"PANW","6":"PANW","7":"PANW","8":"PANW","9":"PANW"},"strike":{"0":50,"1":50,"2":55,"3":55,"4":60,"5":60,"6":65,"7":65,"8":70,"9":70},"symbol":{"0":"PANW241115C00050000","1":"PANW241115P00050000","2":"PANW241115P00055000","3":"PANW241115C00055000","4":"PANW241115P00060000","5":"PANW241115C00060000","6":"PANW241115P00065000","7":"PANW241115C00065000","8":"PANW241115P00070000","9":"PANW241115C00070000"},"trade_date":{"0":0,"1":1709131637656,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"type":{"0":"option","1":"option","2":"option","3":"option","4":"option","5":"option","6":"option","7":"option","8":"option","9":"option"},"underlying":{"0":"PANW","1":"PANW","2":"PANW","3":"PANW","4":"PANW","5":"PANW","6":"PANW","7":"PANW","8":"PANW","9":"PANW"},"volume":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"week_52_high":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0},"week_52_low":{"0":0,"1":0,"2":0,"3":0,"4":0,"5":0,"6":0,"7":0,"8":0,"9":0}}]
//
// Options Clearing Corp Symbols (OCC)
// [{"options":["PANW250117P00280000","PANW250117C00280000","PANW250117P00270000","PANW250117C00270000","PANW250117P00260000","PANW250117P00300000","PANW250117C00260000","PANW250117C00300000","PANW250117P00250000","PANW250117C00250000","PANW250117P00240000","PANW250117C00240000","PANW250117C00286670","PANW250117C00086670","PANW250117C00196670","PANW250117P00086670","PANW250117P00190000","PANW250117C00130000","PANW250117P00313330","PANW250117P00230000","PANW250117P00223330","PANW250117C00213330","PANW250117P00133330","PANW250117C00190000","PANW250117P00266670","PANW250117C00123330","PANW250117C00256670","PANW250117P00176670","PANW250117C00230000","PANW250117C00166670","PANW250117C00293330","PANW250117P00120000","PANW250117C00093330","PANW250117P00093330","PANW250117P00103330","PANW250117P00180000","PANW250117P00236670","PANW250117C00120000","PANW250117C00226670","PANW250117P00146670","PANW250117P00220000","PANW250117C00136670","PANW250117P00273330","PANW250117C00263330","PANW250117P00183330","PANW250117C00180000","PANW250117C00173330","PANW250117C00220000","PANW250117P00206670","PANW250117P00110000","PANW250117P00116670","PANW250117C00106670","PANW250117P00243330","PANW250117C00233330","PANW250117P00153330","PANW250117P00170000","PANW250117P00286670","PANW250117C00110000","PANW250117C00143330","PANW250117P00210000","PANW250117C00276670","PANW250117P00196670","PANW250117C00186670","PANW250117C00170000","PANW250117C00210000","PANW250117P00213330","PANW250117C00203330","PANW250117P00123330","PANW250117C00113330","PANW250117P00256670","PANW250117P00100000","PANW250117C00246670","PANW250117P00166670","PANW250117C00156670","PANW250117P00293330","PANW250117C00283330","PANW250117P00160000","PANW250117C00083330","PANW250117C00100000","PANW250117C00193330","PANW250117P00083330","PANW250117P00200000","PANW250117C00306670","PANW250117P00226670","PANW250117C00160000","PANW250117C00216670","PANW250117P00136670","PANW250117C00200000","PANW250117C00126670","PANW250117P00263330","PANW250117C00253330","PANW250117P00173330","PANW250117C00163330","PANW250117C00096670","PANW250117P00096670","PANW250117P00150000","PANW250117P00106670","PANW250117P00090000","PANW250117P00233330","PANW250117C00313330","PANW250117C00223330","PANW250117P00143330","PANW250117C00150000","PANW250117C00133330","PANW250117P00276670","PANW250117C00266670","PANW250117P00186670","PANW250117C00176670","PANW250117C00090000","PANW250117P00203330","PANW250117P00113330","PANW250117P00140000","PANW250117C00103330","PANW250117P00246670","PANW250117C00236670","PANW250117P00156670","PANW250117P00080000","PANW250117C00146670","PANW250117P00283330","PANW250117C00273330","PANW250117P00193330","PANW250117C00140000","PANW250117C00183330","PANW250117P00306670","PANW250117P00216670","PANW250117C00206670","PANW250117P00126670","PANW250117C00080000","PANW250117C00116670","PANW250117P00253330","PANW250117C00243330","PANW250117P00163330","PANW250117P00130000","PANW250117C00153330","PANW250117C00195000","PANW250117P00125000","PANW250117P00185000","PANW250117C00125000","PANW250117C00185000","PANW250117P00115000","PANW250117P00175000","PANW250117C00115000","PANW250117C00175000","PANW250117P00105000","PANW250117P00165000","PANW250117C00105000","PANW250117C00165000","PANW250117P00155000","PANW250117P00095000","PANW250117C00155000","PANW250117C00095000","PANW250117P00145000","PANW250117C00145000","PANW250117P00135000","PANW250117P00195000","PANW250117C00135000","PANW250117P00085000","PANW250117C00085000","PANW250117C00075000","PANW250117P00075000","PANW250117P00070000","PANW250117C00070000","PANW250620P00110000","PANW250620C00175000","PANW250919P00195000","PANW250919C00135000","PANW250620P00170000","PANW250620C00110000","PANW250620P00105000","PANW250919P00130000","PANW250919C00195000","PANW250620C00170000","PANW250620P00165000","PANW250919P00190000","PANW250620C00105000","PANW250919C00130000","PANW250919P00125000","PANW250620P00100000","PANW250620C00165000","PANW250919C00190000","PANW250919P00185000","PANW250919C00125000","PANW250620P00160000","PANW250620C00100000"],"rootSymbol":"PANW"}]
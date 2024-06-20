// FILE: `src/main.cpp`
#include "Account.h"
#include "EnvReader.h"
#include "EquitiesData.h"
#include "EquityOrder.h"
#include "OptionsOrder.h"
#include "Tradier.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>


//
// Utility Helper Function to Organize Display of Market Data Responses
//

void printTable(const std::vector<std::string>& columnNames, const std::vector<nlohmann::json>& data) {
    // Define column widths
    std::vector<int> columnWidths(columnNames.size(), 10); // Default width of 10 for each column

    // Adjust column widths based on data
    for (const auto& entry : data) {
        for (size_t i = 0; i < columnNames.size(); ++i) {
            int width = entry[columnNames[i]].dump().length();
            if (width > columnWidths[i]) {
                columnWidths[i] = width;
            }
        }
    }

    columnWidths[0] += 1;

    // Print header
    for (size_t i = 0; i < columnNames.size(); ++i) {
        std::cout << std::left << std::setw(columnWidths[i]) << columnNames[i];
    }
    std::cout << std::endl;

    // Print separator
    for (size_t i = 0; i < columnNames.size(); ++i) {
        std::cout << std::setfill('-') << std::setw(columnWidths[i]) << "" << std::setfill(' ');
    }
    std::cout << std::endl;

    // Print data rows
    for (const auto& entry : data) {
        for (size_t i = 0; i < columnNames.size(); ++i) {
            std::cout << std::left << std::setw(columnWidths[i]) << entry[columnNames[i]].dump();
        }
        std::cout << std::endl;
    }
}



int main() {

	//
	// Read authorization token, account number from Python-style environment file
	//

	auto env = loadEnv("../.env");
	std::string accountNumber = env["tradier_acct"];
	std::string authToken = env["tradier_token"];
	bool liveTrade = false;

	//
	// Instantiate Account, EquitiesData, EquityOrder, OptionsOrder classes
	//

	Account myAccount(accountNumber, authToken, liveTrade);
	EquityOrder equityOrder(accountNumber, authToken, liveTrade);
	OptionsOrder optionsOrder(accountNumber, authToken, liveTrade);
	EquitiesData equitiesData(accountNumber, authToken, liveTrade);

	//
	// Retrieve general account information
	//

	std::cout << "!!!!! ACCOUNT DETAILS !!!!!" << std::endl;
	myAccount.fetchAccountDetails();
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;

	//
	// Fetch balance details
	//

	std::cout << "!!!!! ACCOUNT BALANCE DETAILS !!!!!" << std::endl;
	myAccount.fetchBalances();
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Fetch account gain/loss information
	//

	std::cout << "!!!!! GAIN/LOSS INFORMATION !!!!!" << std::endl;
	auto gainLoss = myAccount.getGainLoss();
	std::cout << gainLoss << std::endl;
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Fetch Current Positions
	//

	std::cout << "!!!!! CURRENT POSITIONS !!!!!" << std::endl;
	auto positions = myAccount.getPositions();
	std::cout << positions << std::endl;
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Fetch Current Quotes for DOW 30 Equities
	//

	std::cout << "!!!!! QUOTES - DOW 30 !!!!!" << std::endl;

	std::string symbolList = "AMZN,AXP,AMGN,AAPL,BA,CAT,CSCO,CVX,GS,HD,HON,IBM,INTC,JNJ,KO,JPM,MCD,MMM,MRK,MSFT,NKE,PG,TRV,UNH,CRM,VZ,V,WMT,DIS,DOW";
	auto dowQuotes = equitiesData.getQuotes(symbolList);
	std::cout << dowQuotes << std::endl;

	//
	// Print Quotes in Sequential Blocks
	//

	// for (const auto& quote : dowQuotes) {
	// 	std::cout << "Symbol: " << quote["symbol"] << std::endl;
	// 	std::cout << "Ask: " << quote["ask"] << std::endl;
	// 	std::cout << "Bid: " << quote["bid"] << std::endl;
	// 	std::cout << "Change: " << quote["change"] << std::endl;
	// 	std::cout << "Change (%): " << quote["change_percentage"] << std::endl;
	// 	std::cout << std::endl;
	// }

	//
	// Print Quotes in Tabular Format
	//

	std::cout << std::left 
			  << std::setw(10) << "Symbol"
			  << std::setw(10) << "Ask"
			  << std::setw(10) << "Bid"
			  << std::setw(10) << "Change"
			  << std::setw(10) << "Change (%)"
			  << std::endl;
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;

	for (const auto& quote : dowQuotes) {
		std::cout << std::left
				  << std::setw(10) << quote["symbol"].get<std::string>() << std::fixed << std::setprecision(2)
				  << std::setw(10) << quote["ask"].get<double>()
				  << std::setw(10) << quote["bid"].get<double>()
				  << std::setw(10) << quote["change"].get<double>()
				  << std::setw(10) << quote["change_percentage"].get<double>()
				  << std::endl;
	}
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Fetch Historical Quotes for Apple Incorporated ($AAPL)
	//

	std::cout << "!!!!! HISTORICAL QUOTES - APPLE INC !!!!!" << std::endl;

	std::string appleIncSymbol = "AAPL";
	std::string timescaleInterval = "daily";
	std::string startDate = "2024-05-01";
	std::string endDate = "2024-05-31";
	// std::string sessionFilter = "open"; set to `all` by default in header file declaration

	auto appleHistoricalQuotes = equitiesData.getHistoricalQuotes(appleIncSymbol, timescaleInterval, startDate, endDate);

	std::vector<nlohmann::json> dataHistoricalQuotes = appleHistoricalQuotes;
	std::vector<std::string> colsHistoricalQuotes = {"date", "open", "high", "low", "close", "volume"};

	printTable(colsHistoricalQuotes, dataHistoricalQuotes);
	// std::cout << appleHistoricalQuotes << std::endl;
	// std::cout << appleHistoricalQuotes.dump(4) << std::endl;


	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Options Order to buy QQQ240604C00488000
	//

	std::cout << "!!!!!! OPTIONS ORDER !!!!!" << std::endl;

	std::string occSymbol = "QQQ240604C00488000";
	std::string orderType = "market";
	std::string side = "buy_to_open";
	int quantity = 10;
	std::string underlying = "QQQ";
	double limitPrice = 0.0;
	double stopPrice = 0.0;
	std::string duration = "day";

	auto response = optionsOrder.order(occSymbol, orderType, side, quantity, underlying, limitPrice, stopPrice, duration);
	// std::cout << "Broker Response: " << response.dump(4) << std::endl;
	std::cout << std::setfill('-') << std::setw(55) << "" << std::setfill(' ') << std::endl;
	std::cout << std::endl;


	//
	// Order to buy Apple
	//

	std::cout << "!!!!! EQUITY ORDER !!!!!" << std::endl;

	std::string symbol = "AAPL";
	std::string equitySide = "buy";

	try {
		auto response = equityOrder.order(symbol, equitySide, quantity, orderType);
		std::cout << "Broker Response: " << response.dump(4) << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception occurred: " << e.what() << std::endl;
	}

	return 0;
}



//
// QUOTES OUTPUT SAMPLE - DOW 30 EQUITIES [getQuotes]
//

// Symbol    Ask       Bid       Change    Change (%)
// -------------------------------------------------------
// AMZN      182.73    182.70    -1.25     -0.68     
// AXP       229.43    228.69    1.04      0.46      
// AMGN      306.45    305.99    2.71      0.90      
// AAPL      214.25    214.21    -2.38     -1.10     
// BA        175.24    174.94    -3.40     -1.91     
// CAT       325.50    324.51    2.74      0.85      
// CSCO      45.97     45.96     0.28      0.62      
// CVX       153.46    153.36    0.14      0.10      
// GS        458.15    456.21    7.25      1.61      
// HD        354.35    350.00    4.37      1.25      
// HON       213.40    212.87    0.92      0.44      
// IBM       170.75    170.35    1.05      0.62      
// INTC      30.65     30.63     -0.35     -1.13     
// JNJ       145.71    145.45    -0.30     -0.21     
// KO        62.62     62.61     0.01      0.02      
// JPM       197.09    197.00    2.02      1.04      
// MCD       250.90    250.75    -2.72     -1.08     
// MMM       101.00    100.38    0.24      0.24      
// MRK       128.25    127.90    0.49      0.39      
// MSFT      446.29    446.16    -2.03     -0.46     
// NKE       94.91     94.86     -0.22     -0.24     
// PG        168.67    168.53    1.06      0.64      
// TRV       210.00    207.88    0.38      0.19      
// UNH       482.00    481.36    -8.18     -1.68     
// CRM       231.96    231.35    1.33      0.58      
// VZ        40.14     40.08     0.62      1.58      
// V         273.99    273.04    2.45      0.91      
// WMT       67.59     67.50     0.18      0.27      
// DIS       101.50    101.47    -0.02     -0.02     
// DOW       56.02     55.00     0.21      0.38      
// -------------------------------------------------------





//
// 
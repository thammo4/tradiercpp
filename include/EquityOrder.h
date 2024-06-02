// FILE: `include/EquityOrder.h`
#ifndef EQUITY_ORDER_H
#define EQUITY_ORDER_H

#include <string>
#include "Tradier.h"

class EquityOrder : public Tradier {
public:
	EquityOrder(const std::string& accountNumber, const std::string& authToken, bool liveTrade=false);
	virtual ~EquityOrder();

	nlohmann::json order(
		const std::string& symbol,
		const std::string& side,
		int quantity,
		const std::string& orderType,
		const std::string& duration = "day",
		double limitPrice = 0.0,
		double stopPrice = 0.0
	);
private:
	bool liveTrade;
	std::string ORDER_ENDPOINT;
};

#endif
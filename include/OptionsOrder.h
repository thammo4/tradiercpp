// FILE: `include/OptionsOrder.h`
#ifndef OPTIONSORDER_H
#define OPTIONSORDER_H

#include "Tradier.h"
#include <string>

class OptionsOrder : public Tradier {
public:
	OptionsOrder(const std::string& accountNumber, const std::string& authToken, bool liveTrade = false);
	virtual ~OptionsOrder();

	nlohmann::json order(
		const std::string& occSymbol,
		const std::string& orderType,
		const std::string& side,
		int quantity,
		const std::string& underlying = "",
		double limitPrice = 0.0,
		double stopPrice = 0.0,
		const std::string& duration = "day"
	);
private:
	bool liveTrade;
	std::string ORDER_ENDPOINT;
};

#endif
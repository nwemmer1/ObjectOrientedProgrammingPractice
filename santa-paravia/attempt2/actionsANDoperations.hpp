#pragma once

class Treasury
{
private:
	unsigned currencyGold;
public:
	unsigned addCurrency(unsigned amount);
	unsigned subtractCurrency(unsigned amount);
};
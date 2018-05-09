#pragma once

class Resources
{
private:
	unsigned number;
public:
	void buy(unsigned quantity, treasury &t);
	void sell(unsigned quantity, treasury&t);
	unsigned priceCheck();
};

#ifndef FoodShop_h
#define FoodShop_h

#include "Shop.h"


class FoodShop : protected Shop{

	public:
		FoodShop();
		~FoodShop();
		bool operator=();
		void improve();
		int getLevel();
		int getIncome();
		void setIncome();

	private:
		super();
		int income;
};

#endif // FoodShop_h

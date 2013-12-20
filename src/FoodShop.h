#ifndef FoodShop_h
#define FoodShop_h

#include "Shop.h"


class FoodShop : protected Shop{

	public:
		FoodShop();
		~FoodShop();
		FoodShop operator=();
		void improve();
		int getLevel();
		int getIncome();
		void setIncome();

	private:
		int income;
};

#endif // FoodShop_h

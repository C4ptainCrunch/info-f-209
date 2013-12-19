#ifndef FoodShop_h
#define FoodShop_h

#include "Installation.h"


class FoodShop : protected Installation{

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

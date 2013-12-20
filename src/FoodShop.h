#ifndef FOODSHOP_H
#define FOODSHOP_H

#include "Shop.h"


class FoodShop : public Shop{

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

#endif // FOODSHOP_H

#ifndef FOODSHOP_H
#define FOODSHOP_H

#include "Shop.h"


class FoodShop : public Shop{

    public:
        FoodShop();
        ~FoodShop();
        FoodShop operator=();
};

#endif // FOODSHOP_H

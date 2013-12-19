#ifndef FoodShop_h
#define FoodShop_h

#include "Installation.h"


class FoodShop : public Installation {

 public:

    virtual void getIncome();

 private:
    int income;
};

#endif // FoodShop_h

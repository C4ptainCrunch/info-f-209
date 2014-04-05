#ifndef SHOP_H
#define SHOP_H

#include "Installation.h"
#include <string>

class Shop: public Installation {

public:
    Shop(std::string name, unsigned int income);
    ~Shop();
    unsigned int getIncome();
    void setIncome(unsigned int income);
    std::string getName();

protected:
    unsigned int income_;
    std::string name_;
};

#endif // SHOP_H

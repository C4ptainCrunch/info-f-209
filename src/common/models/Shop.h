#ifndef Shop_h
#define Shop_h

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

#endif // Shop_h

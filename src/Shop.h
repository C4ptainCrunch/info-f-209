#ifndef Shop_h
#define Shop_h

#include "Installation.h"

class Shop : public Installation{

    public:
        Shop(String name,int income);
        ~Shop();
        int getIncome();
        void setIncome();

    protected:
        int income;
        String name;
};

#endif // Shop_h

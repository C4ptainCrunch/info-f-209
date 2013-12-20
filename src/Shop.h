#ifndef Shop_h
#define Shop_h

#include "Installation.h"

class Shop : public Installation{

    public:
        virtual Shop();
        virtual ~Shop();
        virtual Shop operator=();
        virtual int getIncome();
        virtual void setIncome();

    protected:
        int income;
};

#endif // Shop_h

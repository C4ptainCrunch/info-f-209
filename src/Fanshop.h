#ifndef FANSHOP_H
#define FANSHOP_H

#include "Installation.h"

class Fanshop : public Shop{
    public:
        Fanshop();
        ~Fanshop();
        Fanshop operator=();
        void improve();
        int getLevel();
        int getIncome();
        void setIncome();

    private:
        int income;
};

#endif // FANSHOP_H

#ifndef INSTALLATION_h
#define INSTALLATION_h

#include <math.h>

class Installation{

    public:
        Installation(int level = 1);
        ~Installation();
        virtual void improve();
        virtual int improvePrice();
        virtual int getLevel();

    protected:
        int level_;
        static const int baseprice_ = 100;
        static const int powerprice_ = 10;
};

#endif // INSTALLATION_h

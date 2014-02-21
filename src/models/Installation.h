#ifndef INSTALLATION_h
#define INSTALLATION_h

#include <math.h>
#include "../lib/json/json.h"

class Installation{

    public:
        Installation(JsonValue * json);
        Installation(int level = 1);
        ~Installation();
        virtual void improve();
        virtual int improvePrice();
        virtual int getLevel();
        operator JsonValue() const;

    protected:
        int level_;
        static const int baseprice_ = 100;
        static const int powerprice_ = 10;
};

#endif // INSTALLATION_h

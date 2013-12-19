#ifndef Installation_h
#define Installation_h

#include "Club.h"

class Club;

class Installation {

 public:
    virtual void improve();
    virtual int getLevel();

 private:
    int level;
    Club *myClub;
};

#endif // Installation_h

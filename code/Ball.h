#ifndef Ball_h
#define Ball_h

#include "Match.h"

class Match;

class Ball {

 public:
	virtual Ball()
	virtual ~Ball()
	virtual bool operator=(const Ball &ball)
    virtual void move();
    virtual void getSpeed();

 private:
    int speed;

 public:
    Match *myMatch;
};
#endif // Ball_h

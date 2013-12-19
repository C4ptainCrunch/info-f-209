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
    virtual int getSpeed();
    virtual void setSpeed();

 private:
    int speed;
    Match *myMatch;
};
#endif // Ball_h

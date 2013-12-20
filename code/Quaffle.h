#ifndef Quaffle_h
#define Quaffle_h

#include "Ball.h"

class Quaffle: protected Ball{
	public:
		Quaffle();
		~Quaffle();
		bool operator=();
		void move();
		int getSpeed();
		void setSpeed();

};

#endif // Quaffle_h

#ifndef GoldenSnitch_h
#define GoldenSnitch_h

#include "Ball.h"


class GoldenSnitch : protected Ball {

	public:
		GoldenSnitch();
		~GoldenSnitch();
		GoldenSnitch operator=();
		void move();
		int getSpeed();
		void setSpeed();

};

#endif // GoldenSnitch_h

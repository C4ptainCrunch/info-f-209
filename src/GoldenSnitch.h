#ifndef GoldenSnitch_h
#define GoldenSnitch_h

#include "Ball.h"


class GoldenSnitch : public Ball {

	public:
		GoldenSnitch();
		~GoldenSnitch();
		GoldenSnitch operator=();
		void move();

};

#endif // GoldenSnitch_h

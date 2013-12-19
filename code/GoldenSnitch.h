#ifndef GoldenSnitch_h
#define GoldenSnitch_h

#include "Ball.h"
#include "Match.h"

class Match;

class GoldenSnitch : protected Ball {

	public:
		GoldenSnitch();
		~GoldenSnitch();
		bool operator=();
		void move();
		int getSpeed();

	private:
		super();
};

#endif // GoldenSnitch_h

#ifndef Budger_h
#define Budger_h

#include "Ball.h"
#include "Match.h"

class Match;

class Budger : protected Ball{

	public:
		Budger();
		~Budger();
		bool operator=(const Ball &ball);
	    void move();
		void getSpeed();
	
	private:
	    super();
};

#endif // Budger_h

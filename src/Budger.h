#ifndef Budger_h
#define Budger_h

#include "Ball.h"


class Budger : public Ball{

	public:
		Budger();
		~Budger();
		Budger operator=(const Ball &ball);
	    void move();
		void hitPlayer();
};

#endif // Budger_h

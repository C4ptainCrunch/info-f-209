#ifndef Budger_h
#define Budger_h

#include "Ball.h"


class Budger : protected Ball{

	public:
		Budger();
		~Budger();
		bool operator=(const Ball &ball);
	    void move();
		int getSpeed();
		void setSpeed();
		void hitPlayer();
	
	private:
	    super();
};

#endif // Budger_h

#ifndef Fanshop_h
#define Fanshop_h

#include "Installation.h"

class Fanshop : protected Shop{
	public:
		Fanshop();
		~Fanshop();
		bool operator=();
		void improve();
		int getLevel();
		int getIncome();
		void setIncome();

	private:
		super();
		int income;
};

#endif // Fanshop_h

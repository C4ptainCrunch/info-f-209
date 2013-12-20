#ifndef Infirmary_h
#define Infirmary_h

#include "Installation.h"


class Infirmary : protected Installation{

	public:
		Infirmary();
		~Infirmary();
		bool operator=();
		void heal();
		void improve();
		int getLevel();
	private:
		super();
};

#endif // Infirmary_h

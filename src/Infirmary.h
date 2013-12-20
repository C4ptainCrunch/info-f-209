#ifndef Infirmary_h
#define Infirmary_h

#include "Installation.h"


class Infirmary : public Installation{

	public:
		Infirmary();
		~Infirmary();
		Infirmary operator=();
		void heal();
		void improve();
		int getLevel();

};

#endif // Infirmary_h

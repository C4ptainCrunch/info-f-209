#ifndef Infirmary_h
#define Infirmary_h

#include "Installation.h"


class Infirmary : public Installation{

	public:
		Infirmary();
		~Infirmary();
		Infirmary operator=();
		void heal();

};

#endif // Infirmary_h

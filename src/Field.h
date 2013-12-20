#ifndef Field_h
#define Field_h

#include "Installation.h"

class Field : protected Installation{

	public:
		Field();
		~Field();
		Field operator=();
		void improve();
		int getLevel();

};

#endif // Field_h

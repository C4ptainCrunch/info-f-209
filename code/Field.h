#ifndef Field_h
#define Field_h

#include "Installation.h"

class Field : protected Installation{

	public:
		Field();
		~Field();
		bool operator=();
		void improve();
	
	private:
		super();
};

#endif // Field_h

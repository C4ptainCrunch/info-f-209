#ifndef Field_h
#define Field_h

#include "Match.h"
#include "Installation.h"

class Match;

class Field : protected Installation{

	private:
		Match *myMatch;
};

#endif // Field_h

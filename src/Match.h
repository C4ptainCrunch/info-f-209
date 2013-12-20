#ifndef Match_h
#define Match_h

#include "Team.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"

class Team;
class Field;
class GoldenSnitch;
class Quaffle;
class Budger;

class Match{

	public:
		Match();
		~Match();
		Match operator=();
		int getScore();
		void setScore();

	private:
		int teamOneScore;
		int teamTwoScore;
		Team *myTeam[2];
		Field *myField;
		GoldenSnitch *myGoldenSnitch;
		Quaffle *myQuaffle;
		Budger *myBudger[2];
};

#endif // Match_h

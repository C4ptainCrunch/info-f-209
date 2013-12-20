#ifndef MATCH_H
#define MATCH_H

#include "Team.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"

class Match{

    public:
        Match();
        ~Match();
        Match operator=();
        int getScore();
        Team& getTeams();
        GoldenSnitch& getGoldenSnitch();
        Quaffle& getQuaffle();
        Budger& getBudgers();
        void setScore();
        void setTeams();
        void setGoldenSnitch();
		void setQuaffle();
		void setBudgers();

    private:
        int teamOneScore;
        int teamTwoScore;
        Team *myTeam[2];
        Field *myField;
        GoldenSnitch *myGoldenSnitch;
        Quaffle *myQuaffle;
        Budger *myBudgers[2];
};

#endif // MATCH_H

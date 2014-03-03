#ifndef MATCH_H
#define MATCH_H

#include <cmath>
#include <string>
#include <typeinfo>

#include "Club.h"
#include "FieldPlayer.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"
#include "Case.h"
#include "Position.h"

enum { KEEPER = 0, CHASER = 1, BEATER = 2, SEEKER = 3};// 1 KEEPER, 3 CHASERS, 2 BEATERS, 1 SEEKER

enum { host = 0, guest = 1};

class Match{

    public:
        Match(Club& hostClub, Club& guestClub);
        ~Match();
        void movePlayer(int fromX, int fromY,int toX, int toY);
        int* getScore();
        int addPoint(bool guestTeam ,int delta = 1);
        void moveBalls();
        void newTurn(Way playerWays[14]);
        void resolveConflict(Position nextPosition[14], Way playerWays[14], int indexOne, int turnNumber);
        int findIndex(Position nextPosition[14], Position position);
        void movePlayer(Position fromPos, Position toPos);
        void generateFieldPlayers();
        std::string print();//FOR TESTS
        void generateGrid();//TO SET PRIVATE AFTER TESTS

    private:
        bool endGame_ = false;
        FieldPlayer teams_[2][7];
        int score_[2];
        Club *clubs_[2];
        Case grid_[WIDTH][LENGHT];
        GoldenSnitch goldenSnitch_;
        Quaffle quaffle_;
        Budger budgers_[2];
};

#endif // MATCH_H
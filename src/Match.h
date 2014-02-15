#ifndef MATCH_H
#define MATCH_H

#include <cmath>
#include <string>

#include "Club.h"
#include "FieldPlayer.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"
#include "Case.h"
#include "Position.h"

enum { WIDTH = 30, LENGHT = 64};

enum { KEEPER = 0, CHASER = 1, BEATER = 2, SEEKER = 3};// 1 KEEPER, 3 CHASERS, 2 BEATERS, 1 SEEKER


class Match{

    public:
        Match(Club& host, Club& guest);
        ~Match();
        void movePlayer(int fromX, int fromY,int toX, int toY);
        int* getScore();
        int addPoint(bool guestTeam ,int delta = 1);
        void moveBalls();
        bool checkEndOfMatch();
        int* isInTheWay(int fromX,int fromY,int toX, int toY);
        void generateFieldPlayers();
        std::string print();//FOR TESTS
        void generateGrid();//TO SET PRIVATE AFTER TESTS
    private:
        FieldPlayer teams_[2][7];
        int score_[2];
        Club *clubs_[2];
        Case grid_[WIDTH][LENGHT];
        GoldenSnitch goldenSnitch_;
        Quaffle quaffle_;
        Budger budgers_[2];
};

#endif // MATCH_H

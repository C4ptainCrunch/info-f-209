#ifndef MATCH_H
#define MATCH_H

#include <cmath>

#include "Club.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"
#include "Case.h"

enum { WIDTH = 1, LENGHT = 1};

class Match{

    public:
        Match(Club& host, Club& guest);
        ~Match();
        int* getScore();
        int addPoint(bool guestTeam ,int delta = 1);
        void moveBalls();
        bool checkEndOfMatch();
    private:
        void generateGrid();
        int score_[2];
        Club *clubs_[2];
        Case grid_[WIDTH][LENGHT];
        GoldenSnitch goldenSnitch_;
        Quaffle quaffle_;
        Budger budgers_[2];
};

#endif // MATCH_H

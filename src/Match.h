#ifndef MATCH_H
#define MATCH_H

#include "Team.h"
#include "Field.h"
#include "GoldenSnitch.h"
#include "Quaffle.h"
#include "Budger.h"
#include "Case.h"

static const width = 1;
static const length = 1;
class Match{

    public:
        Match(Club & host, Club & guest);
        ~Match();
        int* getScore();
        int addPoint(bool guestTeam ,int delta = 1);

    private:
        int score[2];
        Club *club[2];
        Case grid[width][length];
        GoldenSnitch goldenSnitch;
        Quaffle quaffle;
        Budger budgers[2];
};

#endif // MATCH_H

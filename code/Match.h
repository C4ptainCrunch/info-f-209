#ifndef Match_h
#define Match_h

class Team;
class Field;
class Ball;
class GoldenSnitch;
class Quaffle;
class Budger;

class Match {

 public:

    virtual void getScore();


 private:
    Integer teamOneScore;
    Integer teamTwoScore;

 public:

    /**
     * @element-type Team
     */
    Team *myTeam[ 2];

    Field ** myField;

    /**
     * @element-type Ball
     */
    Ball *myBall[ 4];

    GoldenSnitch *myGoldenSnitch;

    Quaffle *myQuaffle;

    /**
     * @element-type Budger
     */
    Budger *myBudger[ 2];
};

#endif // Match_h

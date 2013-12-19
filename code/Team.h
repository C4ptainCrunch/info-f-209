#ifndef Team_h
#define Team_h

class Club;
class Player;
class Match;
class NonFieldPlayer;

class Team {

 public:

    virtual void newOperation();

 public:

    Club *myClub;

    /**
     * @element-type Player
     */
    Player *myPlayer[ 7];

    /**
     * @element-type Player
     */
    Player *myPlayer;

    /**
     * @element-type Player
     */
    Player *myPlayer;

    /**
     * @element-type Player
     */
    Player *0[ 7];

    Match *myMatch;

    /**
     * @element-type Player
     */
    Player *myPlayer;

    /**
     * @element-type Player
     */
    Player *myPlayer[ 7];

    /**
     * @element-type NonFieldPlayer
     */
    NonFieldPlayer *myNonFieldPlayer[ 7];
};

#endif // Team_h

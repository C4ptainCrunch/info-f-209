#ifndef Player_h
#define Player_h

class Team;
class Bench;

class Player {

 public:

    virtual void getSpeed();

    virtual void getForce();

    virtual void getAgility();

    virtual void getReflexes();

    virtual void getPassPrecision();

 public:
    Integer inventory;

 private:
    Integer speed;
    Integer force;
    Integer agility;
    Integer reflexes;
    Integer passPrecision;

 public:

    Team *myTeam;

    /**
     * @element-type Team
     */
    Team *myTeam;

    /**
     * @element-type Team
     */
    Team *myTeam;

    Team *0;

    /**
     * @element-type Team
     */
    Team *myTeam;

    Team *myTeam;

    /**
     * @element-type Bench
     */
    Bench *myBench;
};

#endif // Player_h

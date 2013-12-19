#ifndef Player_h
#define Player_h


class Player {

 public:

    virtual int getSpeed();
    virtual int getForce();
    virtual int getAgility();
    virtual int getReflexes();
    virtual int getPassPrecision();

 private:
    int speed;
    int force;
    int agility;
    int reflexes;
    int passPrecision;
    void inventory[];
};

#endif // Player_h

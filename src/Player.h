#ifndef Player_h
#define Player_h


class Player{

    public:
        virtual Player();
        virtual ~Player();
        virtual Player operator=();
        virtual int getSpeed();
        virtual int getForce();
        virtual int getAgility();
        virtual int getReflexes();
        virtual int getPassPrecision();
        virtual bool isWounded();
        virtual void getInventory();
        virtual void setSpeed();
        virtual void setForce();
        virtual void setAgility();
        virtual void setReflexes();
        virtual void setPassPrecision();
        virtual void setWoundState();
        virtual void setInventory();
        

    protected:
        int speed;
        int force;
        int agility;
        int reflexes;
        int passPrecision;
        bool wounded=False;
        int inventory[];
};

#endif // Player_h

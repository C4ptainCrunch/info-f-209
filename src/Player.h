#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player{

    public:
        Player(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, vector<Item> inventory);
        Player();
        virtual ~Player();
        virtual int getSpeed();
        virtual int getForce();
        virtual int getAgility();
        virtual int getReflexes();
        virtual int getPassPrecision();
        virtual bool isWounded();
        virtual vector<Item> getInventory();
        virtual void setSpeed(int speed);
        virtual void setForce(int force);
        virtual void setAgility(int agility);
        virtual void setReflexes(int reflexes);
        virtual void setPassPrecision(int passPrecision);
        virtual void setWoundState(bool woundState);
        Item removeItem(string itemType);
        Item removeItem(int position);
        virtual void addToInventory(Item newItem);

    protected:
        int speed_;
        int force_;
        int agility_;
        int reflexes_;
        int passPrecision_;
        bool wounded_;
        vector<Item> inventory_;
};

#endif // PLAYER_H

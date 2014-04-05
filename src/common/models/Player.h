#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Item.h"

class Player {

public:
    Player(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory);
    Player();
    virtual ~Player();
    virtual int getSpeed() const;
    virtual int getForce() const;
    virtual int getAgility() const;
    virtual int getReflexes() const;
    virtual int getPassPrecision() const;
    virtual bool isWounded() const;
    virtual void setWoundedState(bool wound);
    virtual std::vector<Item> getInventory() const;
    virtual void setSpeed(int speed);
    virtual void setForce(int force);
    virtual void setAgility(int agility);
    virtual void setReflexes(int reflexes);
    virtual void setPassPrecision(int passPrecision);
    virtual void setWoundState(bool woundState);

protected:
    int speed_;
    int force_;
    int agility_;
    int reflexes_;
    int passPrecision_;
    bool wounded_;
    std::vector<Item> inventory_;
};

#endif // PLAYER_H

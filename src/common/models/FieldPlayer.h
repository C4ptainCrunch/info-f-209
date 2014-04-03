#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"
#include "NonFieldPlayer.h"


class FieldPlayer: public Player {

public:
    FieldPlayer(int role, bool guest);
    FieldPlayer(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory, int role, bool guest);
    FieldPlayer();
    FieldPlayer(JsonValue * json);
    ~FieldPlayer();
    FieldPlayer(NonFieldPlayer & nonFieldPlayer, int role, bool guest);
    FieldPlayer & operator=(Player & player);
    void move();
    void hitBudger();
    void catchGoldenSnitch();
    void throwQuaffle();
    void catchQuaffle();
    void testMove();
    bool isInGuestTeam();
    int getRole();
    void setRole(int role);
    operator JsonDict() const;
private:
    bool guest_;
    int role_;

};

#endif // FIELDPLAYER_H

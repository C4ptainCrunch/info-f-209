#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"
#include "NonFieldPlayer.h"


class FieldPlayer : public Player{

    public:
        FieldPlayer(int role);
        FieldPlayer();
        ~FieldPlayer();
        FieldPlayer(NonFieldPlayer& nonFieldPlayer, int role);
        FieldPlayer& operator=(Player& player);
        void move();
        void hitBudger();
        void catchGoldenSnitch();
        void throwQuaffle();
        void catchQuaffle();
        void testMove();
        void initializeId();
        int getId();
        int getRole();
        void setRole(int role);
    private:
        static int nextID_;
        int role_;
        int id_;

};

#endif // FIELDPLAYER_H

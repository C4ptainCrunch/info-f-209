#ifndef NONFIELDPLAYER_H
#define NONFIELDPLAYER_H

#include "Player.h"

class NonFieldPlayer : public Player{

    public:
        NonFieldPlayer();
        ~NonFieldPlayer();
        NonFieldPlayer operator=();
        int getLevel();
        void setExp();
        void levelUp();
        int getVocation();
        void setVocation();

    private:
        int level;
        int vocation;
};

#endif // NONFIELDPLAYER_H

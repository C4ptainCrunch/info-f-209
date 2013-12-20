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
        void vocation();

    private:
        int level;
        void vocation;
};

#endif // NONFIELDPLAYER_H

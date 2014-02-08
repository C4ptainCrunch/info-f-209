#ifndef NONFIELDPLAYER_H
#define NONFIELDPLAYER_H

#include "Player.h"

class NonFieldPlayer : public Player{

    public:
        NonFieldPlayer(int vocation, int level = 1, int experience = 0);
        ~NonFieldPlayer();
        NonFieldPlayer & operator=(const Player & player);
        int getLevel();
        void changeExperience(int deltaExperience);
        void levelUp();
        int getVocation();
        void setVocation(int vocation);

    private:
        int level_;
        int experience_;
        int vocation_;
};

#endif // NONFIELDPLAYER_H

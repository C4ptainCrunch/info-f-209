#ifndef NONFIELDPLAYER_H
#define NONFIELDPLAYER_H

#include "Player.h"
#include "../lib/json/json.h"

class NonFieldPlayer : public Player{

    public:
        NonFieldPlayer(int vocation, int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory, int level = 1, int experience = 0);
        NonFieldPlayer(JsonValue * json);
        NonFieldPlayer();
        ~NonFieldPlayer();
        NonFieldPlayer & operator=(const Player & player);
        operator JsonValue() const;
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

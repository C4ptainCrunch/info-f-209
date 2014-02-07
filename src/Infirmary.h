#ifndef INFIRMARY_H
#define INFIRMARY_H

#include "Installation.h"
#include "Player.h"


class Infirmary : public Installation{

    public:
        Infirmary(int level);
        ~Infirmary();
        void heal(Player& player);
};

#endif // INFIRMARY_H

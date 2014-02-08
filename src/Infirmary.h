#ifndef INFIRMARY_H
#define INFIRMARY_H

#include "Installation.h"
#include "Player.h"


class Infirmary : public Installation{

    public:
        Infirmary(int level = 1);
        ~Infirmary();
        void heal(Player& player);
};

#endif // INFIRMARY_H

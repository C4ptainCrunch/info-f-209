#ifndef INFIRMARY_H
#define INFIRMARY_H

#include "Installation.h"


class Infirmary : public Installation{

    public:
        Infirmary();
        ~Infirmary();
        Infirmary operator=();
        void heal();
};

#endif // INFIRMARY_H

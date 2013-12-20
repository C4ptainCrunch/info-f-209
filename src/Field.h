#ifndef FIELD_H
#define FIELD_H

#include "Installation.h"

class Field : public Installation{

    public:
        Field();
        ~Field();
        Field operator=();
        void improve();
        int getLevel();

};

#endif // FIELD_H

#ifndef TRAININGFIELD_H
#define TRAININGFIELD_H

#include "Installation.h"

class TrainingField : public Installation{
    
    public:
        TrainingField();
        ~TrainingField();
        TrainingField operator=();
        void training();

};

#endif // TRAININGFIELD_H

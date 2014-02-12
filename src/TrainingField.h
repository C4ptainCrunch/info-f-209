#ifndef TRAININGFIELD_H
#define TRAININGFIELD_H

#include "Installation.h"
#include "NonFieldPlayer.h"

class TrainingField : public Installation{

    public:
        TrainingField();
        ~TrainingField();
        TrainingField operator=(TrainingField& trainingField);
        void training(NonFieldPlayer& player);

};

#endif // TRAININGFIELD_H

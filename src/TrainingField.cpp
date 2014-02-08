#include "TrainingField.h"

TrainingField::TrainingField() : Installation(1){}

TrainingField::~TrainingField(){}

//TrainingField TrainingField::operator=(TrainingField& trainingField){}

void TrainingField::training(NonFieldPlayer& player){
	player.changeExperience(level_*100);
}

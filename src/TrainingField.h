#ifndef TrainingField_h
#define TrainingField_h

#include "Installation.h"

class TrainingField : public Installation{
	
	public:
		TrainingField();
		~TrainingField();
		TrainingField operator=();
		void improve();
		int getLevel();
		void training();
	
};

#endif // TrainingField_h

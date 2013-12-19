#ifndef TrainingField_h
#define TrainingField_h

#include "Installation.h"

class TrainingField : protected Installation{
	
	public:
		TrainingField();
		~TrainingField();
		bool operator=();
		void improve();
		int getLevel();
		void training();

	private:
		super();
	
};

#endif // TrainingField_h

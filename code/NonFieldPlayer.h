#ifndef NonFieldPlayer_h
#define NonFieldPlayer_h

#include "Player.h"

class NonFieldPlayer : protected Player{

	public:
		super();
		NonFieldPlayer();
		~NonFieldPlayer();
		bool operator=();
		int getLevel();
		void setExp();
		void levelUp();
		void Vocation();

	private:
		super();
		int level;
		void vocation;
};

#endif // NonFieldPlayer_h

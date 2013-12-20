#ifndef NonFieldPlayer_h
#define NonFieldPlayer_h

#include "Player.h"

class NonFieldPlayer : public Player{

	public:
		NonFieldPlayer();
		~NonFieldPlayer();
		NonFieldPlayer operator=();
		int getLevel();
		void setExp();
		void levelUp();
		void vocation();

	private:
		int level;
		void vocation;
};

#endif // NonFieldPlayer_h

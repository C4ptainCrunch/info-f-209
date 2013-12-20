#ifndef Team_h
#define Team_h

#include "Player.h"
#include "NonFieldPlayer.h"

class Team{

	public:
		Team();
		~Team();
		Team operator=();
		void newOperation();
		Player* getPlayers();
		NonFieldPlayer* getNonFieldPlayers();
		void getPlayers();
		void setNonFieldPlayers();

	private:
		Player *myPlayer[ 7];
		NonFieldPlayer *myNonFieldPlayer[ 7];
};

#endif // Team_h

#ifndef Club_h
#define Club_h

#include <vector>
#include "Installation.h"
#include "Manager.h"
#include "Team.h"
#include "NonFieldPlayer.h"

class Club {

	public:
		Club();
		~Club();
		Club operator=();
		int getMoney();
		void addMoney();
		void lowerMoney();
		int getLevel();
		void levelUp();
		Manager& getManager();
		Team& getTeam();
		std::vector< Installation* > getInstallations();
		std::vector< NonFieldPlayer* > getNonFieldPlayers();
		void setManager();
		void setTeam();
		void setInstallations();
		void setNonFieldPlayers();

	private:
		int money;
		int level;
		std::vector< Installation* > myInstallation;
		Manager *myManager;
		Team *myTeam;
		std::vector< NonFieldPlayer* > myNonFieldPlayer;
};

#endif // Club_h

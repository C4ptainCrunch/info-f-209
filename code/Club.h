#ifndef Club_h
#define Club_h

#include <vector>
#include "Installation.h"
#include "Manager.h"
#include "Team.h"
#include "Bench.h"
#include "NonFieldPlayer.h"

class Installation;
class Manager;
class Team;
class Bench;
class NonFieldPlayer;

class Club {

	public:
		Club();
		~Club();
		bool operator=();
		int getMoney();
		void addMoney();
		void lowerMoney();
		int getLevel();
		void levelUp();
		Manager& getManager();
		Team& getTeam();
		Bench& getBench;
		std::vector< Installation* > getInstallations();
		std::vector< NonFieldPlayer* > getNonFieldPlayers();
		void setManager();
		void setTeam();
		void setBench();
		void setInstallations();
		void setNonFieldPlayers();

	private:
		int money;
		int level;
		std::vector< Installation* > myInstallation;
		Manager *myManager;
		Team *myTeam;
		Bench *myBench;
		std::vector< NonFieldPlayer* > myNonFieldPlayer;
};

#endif // Club_h

#include "Club.h"
#include "Match.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	/*
	TODO instancier les FieldPlayers a partir de NonField
	NonFieldPlayer *playersT1[7]; 
	NonFieldPlayer *playersT2[7];

	playersT1[0] = new NonFieldPlayer();
	playersT1[0]->setRole(KEEPER);

	playersT1[1] = new NonFieldPlayer();
	playersT1[1]->setRole(CHASER);

	playersT1[2] = new NonFieldPlayer();
	playersT1[2]->setRole(CHASER);

	playersT1[3] = new NonFieldPlayer();
	playersT1[3]->setRole(CHASER);

	playersT1[4] = new NonFieldPlayer();
	playersT1[4]->setRole(BEATER);

	playersT1[5] = new NonFieldPlayer();
	playersT1[5]->setRole(BEATER);

	playersT1[6] = new NonFieldPlayer();
	playersT1[6]->setRole(SEEKER);


	playersT2[0] = new NonFieldPlayer();
	playersT2[0]->setRole(KEEPER);

	playersT2[1] = new NonFieldPlayer();
	playersT2[1]->setRole(CHASER);

	playersT2[2] = new NonFieldPlayer();
	playersT2[2]->setRole(CHASER);

	playersT2[3] = new NonFieldPlayer();
	playersT2[3]->setRole(CHASER);

	playersT2[4] = new NonFieldPlayer();
	playersT2[4]->setRole(BEATER);

	playersT2[5] = new NonFieldPlayer();
	playersT2[5]->setRole(BEATER);

	playersT2[6] = new NonFieldPlayer();
	playersT2[6]->setRole(SEEKER);

	Team teamOne();
	*/
	Club host = Club();
	Club guest = Club();
	Match match = Match(host,guest);
	string x = match.print();
	cout<<x<<endl;
	bool ended = false;
	/*
	while (not ended){
		//L'utilisateur choisit quels pions et ou le bouger
		match.moveBalls();
		//passe la main a l'autre utilisateur

	}
	*/
	return 0;
}
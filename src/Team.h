#ifndef Team_h
#define Team_h

class Player;
class NonFieldPlayer;

class Team {

	public:
		Team();
		~Team();
		Team operator=();
		void newOperation();

	private:
		Player *myPlayer[ 7];
		NonFieldPlayer *myNonFieldPlayer[ 7];
};

#endif // Team_h

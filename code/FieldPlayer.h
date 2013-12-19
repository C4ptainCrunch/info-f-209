#ifndef FieldPlayer_h
#define FieldPlayer_h

#include "Player.h"


class FieldPlayer : protected Player{

	public:
		FieldPlayer();
		~FieldPlayer();
		bool operator=();
		void move();
		void hitBludger();
		void catchSnitch();
		void throwQuaffle();
		void catchQuaffle();
		void testMove();
};

#endif // FieldPlayer_h

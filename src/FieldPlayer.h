#ifndef FieldPlayer_h
#define FieldPlayer_h

#include "Player.h"

class FieldPlayer : public Player{

	public:
		FieldPlayer();
		~FieldPlayer();
		FieldPlayer operator=();
		void move();
		void hitBludger();
		void catchSnitch();
		void throwQuaffle();
		void catchQuaffle();
		void testMove();

};

#endif // FieldPlayer_h

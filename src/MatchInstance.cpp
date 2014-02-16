#include "Club.h"
#include "Match.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    // NonFieldPlayer *playersT1[7]; 
    // NonFieldPlayer *playersT2[7];


    // playersT2[0] = new NonFieldPlayer();

    // playersT2[1] = new NonFieldPlayer();
    // playersT2[2] = new NonFieldPlayer();

    // playersT2[3] = new NonFieldPlayer();

    // playersT2[4] = new NonFieldPlayer();

    // playersT2[5] = new NonFieldPlayer();

    // playersT2[6] = new NonFieldPlayer();

    // Team teamOne(playersT1);
    // Team teamTwo(playersT2);
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
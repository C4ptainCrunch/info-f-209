#include "match.h"

using namespace std;

namespace views {

void end_turn(JsonValue * message, UserHandler * handler){
    JsonList * listMessage = JLIST(message);
    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }
    Way playerWays[7];
    for(int i = 0; i < listMessage->size() && i < 7; i++){
        JsonList * way = JLIST((*listMessage)[i]);
        if (way == NULL) {
            throw BadRequest("Malformatted request. Need a JSON dict");
        }
        Way newWay;
        for(int j = 0; j < way->size(); j++){
            JsonList * listPos = JLIST((*way)[j]);
            if (listPos == NULL) {
                throw BadRequest("Malformatted request. Need a JSON dict");
            }
            Position pos;
            JsonInt * intX = JINT((*listPos)[0]);
            JsonInt * intY = JINT((*listPos)[1]);
            if (intX == NULL || intY == NULL) {
                throw BadRequest("Malformatted request. Need a JSON dict");
            }
            pos.x = *intX;
            pos.y = *intY;
            newWay.push_back(pos);
        }
        playerWays[i] = newWay;
    }
    for(int i = listMessage->size(); i < 7; i++){
        playerWays[i] = Way();
    }

    Club * club = handler->getManager()->getClub();
    Match * match = handler->getMatch();
    bool isGuest = match->isGuest(club);
    match->setWays(isGuest, playerWays);
}

}

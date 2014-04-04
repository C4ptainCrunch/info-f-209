#include "match.h"

using namespace std;

namespace views {

void end_turn(JsonValue * message, UserHandler * handler) {
    JsonList * listMessage = JLIST(message);
    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }
    Way playerWays[7];
    for (int i = 0; i < listMessage->size() && i < 7; i++) {
        JsonList * way = JLIST((*listMessage)[i]);
        if (way == NULL) {
            throw BadRequest("Malformatted request. Need a JSON dict");
        }
        Way newWay;
        for (int j = 0; j < way->size(); j++) {
            JsonList * listPos = JLIST((*way)[j]);
            if (listPos == NULL) {
                throw BadRequest("Malformatted request. Need a JSON dict");
            }
            Position pos;
            JsonInt * intX = JINT((*listPos)[0]);
            JsonInt * intY = JINT((*listPos)[1]);
            if ((intX == NULL) || (intY == NULL)) {
                throw BadRequest("Malformatted request. Need a JSON dict");
            }
            pos.x = *intX;
            pos.y = *intY;
            newWay.push_back(pos);
        }
        playerWays[i] = newWay;
    }
    for (int i = listMessage->size(); i < 7; i++) {
        playerWays[i] = Way();
    }

    Club * club = handler->getManager()->getClub();
    Match * match = handler->getMatch();
    bool isGuest = match->isGuest(club);
    match->setWays(isGuest, playerWays);
    if(match->setReady(isGuest)){
        if(match->newTurn()){

            Challenge * challenge = NULL;
            int i;
            for (i = 0; i < handler->getChalenge_list()->size() && challenge == NULL; i++) {
                if (handler->getChalenge_list()->at(i).opponents[0] == handler->getManager() || handler->getChalenge_list()->at(i).opponents[1] == handler->getManager()) {
                    challenge = &(handler->getChalenge_list()->at(i));
                    cout<<challenge<<endl;
                }
            }
            i--; // Decrement the last loop
            if (challenge == NULL) {
                cout<<"Challenge does not exist"<<endl;
                return sendFail(handler, 406, "challenge", "Challenge does not exist");
            }
            if ((challenge->opponents[0] != handler->getManager()) && (challenge->opponents[1] != handler->getManager())) {
                cout<<"Challenge is not yours"<<endl;
                return sendFail(handler, 407, "challenge", "This challenge is not yours");
            }


            UserHandler * other_handler;
            if (challenge->opponents[0] == handler->getManager()) {
                other_handler = handler->findHandler(challenge->opponents[1]);
            }
            else {
                other_handler = handler;
                handler = handler->findHandler(challenge->opponents[1]);
            }

            if(match->getScore()[0] > match->getScore()[1]){
                //Host win
                handler->writeToClient("end_match", new JsonInt(EndMatch::WIN));
                other_handler->writeToClient("end_match", new JsonInt(EndMatch::LOSE));
            }
            else{
                //Guest win
                handler->writeToClient("end_match", new JsonInt(EndMatch::LOSE));
                other_handler->writeToClient("end_match", new JsonInt(EndMatch::WIN));
            }
            handler->getChalenge_list()->erase(handler->getChalenge_list()->begin() + i);
            cout << "END" << endl;
        }
        else{
            // updateMatch(json Match)
            Challenge * challenge = NULL;
            int i;
            for (i = 0; i < handler->getChalenge_list()->size() && challenge == NULL; i++) {
                if (handler->getChalenge_list()->at(i).opponents[0] == handler->getManager() || handler->getChalenge_list()->at(i).opponents[1] == handler->getManager()) {
                    challenge = &(handler->getChalenge_list()->at(i));
                    cout<<challenge<<endl;
                }
            }
            i--; // Decrement the last loop
            if (challenge == NULL) {
                cout<<"Challenge does not exist"<<endl;
                return sendFail(handler, 406, "challenge", "Challenge does not exist");
            }
            if ((challenge->opponents[0] != handler->getManager()) && (challenge->opponents[1] != handler->getManager())) {
                cout<<"Challenge is not yours"<<endl;
                return sendFail(handler, 407, "challenge", "This challenge is not yours");
            }


            UserHandler * other_handler;
            if (challenge->opponents[0] == handler->getManager()) {
                other_handler = handler->findHandler(challenge->opponents[1]);
            }
            else {
                other_handler = handler->findHandler(challenge->opponents[0]);
            }

            JsonDict payload = (JsonDict) * match;
            cout << match->print()<<endl;
            handler->writeToClient("updateMatch", &payload);
            other_handler->writeToClient("updateMatch", &payload);
        }
    }
}

void surrender(JsonValue* message, UserHandler * handler) {
    JsonInt * id_int = JINT(message);
    if (id_int == NULL) {
        throw BadRequest("Malformatted request. Need a JSON int");
    }
    int challenge_id = *id_int;
    Challenge * challenge = NULL;
    int i;
    cout<<"TAILLE : "<<handler->getChalenge_list()->size() <<endl;
    for (i = 0; i < handler->getChalenge_list()->size() && challenge == NULL; i++) {
        cout<<"i : "<<i<<endl;
        if (handler->getChalenge_list()->at(i).id == challenge_id) {
            challenge = &(handler->getChalenge_list()->at(i));
            cout<<challenge<<endl;
        }
    }
    i--; // Decrement the last loop
    if (challenge == NULL) {
        cout<<"Challenge does not exist"<<endl;
        return sendFail(handler, 406, "challenge", "Challenge does not exist");
    }
    if ((challenge->opponents[0] != handler->getManager()) && (challenge->opponents[1] != handler->getManager())) {
        cout<<"Challenge is not yours"<<endl;
        return sendFail(handler, 407, "challenge", "This challenge is not yours");
    }


    UserHandler * other_handler;
    if (challenge->opponents[0] == handler->getManager()) {
        other_handler = handler->findHandler(challenge->opponents[1]);
    }
    else {
        other_handler = handler->findHandler(challenge->opponents[0]);
    }

    handler->writeToClient("end_match", new JsonInt(EndMatch::SURRENDER_LOSE));
    other_handler->writeToClient("end_match", new JsonInt(EndMatch::SURRENDER_WIN));

    handler->getChalenge_list()->erase(handler->getChalenge_list()->begin() + i);
}

}

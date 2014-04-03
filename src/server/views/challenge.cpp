#include "challenge.h"

using namespace std;

namespace views {

void challenge(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = castDict(message);

    string other_username = getString(dictMessage, "other_username");
    UserHandler * other_handler = handler->findHandler(other_username);
    if (other_handler == NULL) {
        return sendFail(handler, 301, "challenge", "User does not exist");
    }
    if (other_handler == handler) {
        return sendFail(handler, 999, "challenge", "You cannot challenge yourself");
    }

    // TODO : should test if the remote user has already a challenge

    server_shared_data * server_data = handler->getSharedData();
    Challenge current_challenge = {
        server_data->last_challenge_id++,
        {
            handler->getManager(),
              other_handler->getManager()
        }
    };
    handler->getChalenge_list()->push_back(current_challenge);

    JsonDict * payload = new JsonDict();
    payload->add("remote_username", new JsonString(handler->getManager()->getUserName()));
    payload->add("remote_name", new JsonString(handler->getManager()->getName()));
    payload->add("challenge_id", new JsonInt(current_challenge.id));
    other_handler->writeToClient("challenge", payload);
}

void accept_challenge(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = castDict(message);
    int challenge_id = getInt(dictMessage, "id");
    Challenge * challenge = NULL;
    int i;
    for (i = 0; i < handler->getChalenge_list()->size() && challenge == NULL; i++) {
        if (handler->getChalenge_list()->at(i).id == challenge_id) {
            challenge = &(handler->getChalenge_list()->at(i));
        }
    }
    i--; // Decrement the last loop
    if (challenge == NULL) {
        return sendFail(handler, 999, "challenge", "Challenge does not exist");
    }
    if ((challenge->opponents[0] != handler->getManager()) && (challenge->opponents[1] != handler->getManager())) {
        return sendFail(handler, 999, "challenge", "This challenge is not yours");
    }

    Match * match = new Match(*(challenge->opponents[0]->getClub()), *(challenge->opponents[1]->getClub()));
    handler->getMatch_list()->push_back(match);
    handler->getChalenge_list()->erase(handler->getChalenge_list()->begin() + i);

    UserHandler * other_handler;
    if (challenge->opponents[0] == handler->getManager()) {
        other_handler = handler->findHandler(challenge->opponents[1]);
    }
    else {
        other_handler = handler->findHandler(challenge->opponents[0]);
    }

    JsonDict payload = (JsonDict) * match;
    other_handler->writeToClient("match_begin", &payload);
    handler->writeToClient("match_begin", &payload);

}

void refuse_challenge(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = castDict(message);
    int challenge_id = getInt(dictMessage, "id");
    Challenge * challenge = NULL;
    int i;
    for (i = 0; i < handler->getChalenge_list()->size() && challenge == NULL; i++) {
        if (handler->getChalenge_list()->at(i).id == challenge_id) {
            challenge = &(handler->getChalenge_list()->at(i));
        }
    }
    i--; // Decrement the last loop
    if (challenge == NULL) {
        return sendFail(handler, 999, "challenge", "Challenge does not exist");
    }
    if ((challenge->opponents[0] != handler->getManager()) && (challenge->opponents[1] != handler->getManager())) {
        return sendFail(handler, 999, "challenge", "This challenge is not yours");
    }


    UserHandler * other_handler;
    if (challenge->opponents[0] == handler->getManager()) {
        other_handler = handler->findHandler(challenge->opponents[1]);
    }
    else {
        other_handler = handler->findHandler(challenge->opponents[0]);
    }

    JsonDict payload = JsonDict();
    payload.add("challenge_id", new JsonInt(challenge->id));
    other_handler->writeToClient("refuse_challenge", &payload);

    handler->getChalenge_list()->erase(handler->getChalenge_list()->begin() + i);

}


} // end namespace

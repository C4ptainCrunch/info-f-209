#include "user.h"

using namespace std;

namespace views {

void playerlist(JsonValue * message, UserHandler * handler) {
    Manager * manager = handler->getManager();
    JsonList * playerslist;
    if ((manager != NULL)) {
        playerslist = new JsonList();
        vector<NonFieldPlayer *> players = manager->getClub()->getNonFieldPlayers();
        for (int i = 0; i < players.size(); i++) {
            JsonDict * player = new JsonDict(*(players[i]));
            playerslist->add(player);
        }
    }
    handler->writeToClient("playerlist", playerslist);
}
}

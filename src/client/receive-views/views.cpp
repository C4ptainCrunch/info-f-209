#include "views.h"

using namespace std;

namespace rviews {

void login(JsonValue * message, ServerHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    bool success = getBool(dictMessage, "success");
    if (success) {
        emit handler->getWindow()->loginSuccess();
    }
    else {
        emit handler->getWindow()->loginFailure(getInt(dictMessage, "code"));
    }
}

void signup(JsonValue * message, ServerHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    bool success = getBool(dictMessage, "success");
    if (success) {
        emit handler->getWindow()->registerSuccess();
    }
    else {
        emit handler->getWindow()->registerFailure(getInt(dictMessage, "code"));
    }
}

void userlist(JsonValue * message, ServerHandler * handler) {
    JsonList * listMessage = JLIST(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    vector<string> * ulist = new vector<string>;
    for (size_t i = 0; i < listMessage->size(); i++) {
        ulist->push_back(getString(listMessage, i));
    }
    emit handler->getWindow()->userList(ulist);
}

void playerlist(JsonValue * message, ServerHandler * handler) {
    JsonList * listMessage = JLIST(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    vector<NonFieldPlayer *> * plist = new vector<NonFieldPlayer *>;
    for (size_t i = 0; i < listMessage->size(); i++) {
        plist->push_back(new NonFieldPlayer((*listMessage)[i]));
    }
    emit handler->getWindow()->playerList(plist);
}

void challenge(JsonValue  * message, ServerHandler * handler) {
    JsonDict * listMessage = castDict(message);

    string * opponentName = new string(getString(listMessage, "remote_name"));
    int matchID = getInt(listMessage, "challenge_id");
    emit handler->getWindow()->newDefi(opponentName, matchID);

}

void startMatch(JsonValue * message, ServerHandler * handler) {
    JsonDict * listMessage = JDICT(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    bool isGuest = getBool(listMessage, "guest");
    int matchID = getInt(listMessage, "id");

    Match * match = new Match(listMessage);
    emit handler->getWindow()->startMatch(match, isGuest, matchID);
}

void updateMatch(JsonValue * message, ServerHandler * handler) {
    JsonDict * listMessage = JDICT(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    Match * match = new Match(listMessage);
    emit handler->getWindow()->updateMatch(match);
}

void endMatch(JsonValue * message, ServerHandler * handler) {
    JsonInt * result_int = JINT(message);

    if (result_int == NULL) {
        throw BadRequest("Malformatted request. Need a JSON int");
    }

    int result = *result_int;
    emit handler->getWindow()->endMatch(result);
}

}

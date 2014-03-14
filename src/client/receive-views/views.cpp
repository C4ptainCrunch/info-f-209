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
    for (int i = 0; i < listMessage->size(); i++) {
        ulist->push_back(getString(listMessage, i));
    }
    emit handler->getWindow()->userList(ulist);
}

void playerlist(JsonValue * message, ServerHandler * handler) {
    JsonList * listMessage = JLIST(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    vector<NonFieldPlayer*> * plist = new vector<NonFieldPlayer*>;
    for (int i = 0; i < listMessage->size(); i++) {
        plist->push_back(new NonFieldPlayer((*listMessage)[i]));
    }
    emit handler->getWindow()->playerList(*plist);
}

}

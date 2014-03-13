#include "views.h"

using namespace std;

namespace rviews {

void login(JsonValue * message, ServerHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    bool success = getBool(dictMessage, "success");
    if(success){
        emit handler->getWindow()->loginSuccess();
    }
    else {
        emit handler->getWindow()->loginFailure(getString(dictMessage, "reason"));
    }
}

void signup(JsonValue * message, ServerHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    bool success = getBool(dictMessage, "success");
    if(success){
        emit handler->getWindow()->registerSuccess();
    }
    else {
        emit handler->getWindow()->registerFailure(getInt(dictMessage, "code"));
    }
}

void userlist(JsonValue * message, ServerHandler * handler) {
    JsonDict * listMessage = JLIST(message);

    if (listMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON list");
    }

    bool success = getBool(dictMessage, "success");
    if(success){
        JsonList * jlist = getList(dictMessage, "userlist");
        vector<string> ulist;
        for(int i = 0; i < jlist->size(); i++){
            ulist.push_back(getString(jlist, i));
        }
        emit handler->getWindow()->userlist(ulist);
    }
    else {
        emit handler->getWindow()->registerFailure(getInt(dictMessage, "code"));
    }
}



// void userlist(JsonValue * message, UserHandler * handler) {
//     JsonList answer;
//     std::vector<UserHandler *> handlers_vector = *(handler->getHandlers_listPtr());

//     for (int i = 0; i < handlers_vector.size(); i++) {
//         Manager * manager = handlers_vector[i]->getManager();
//         if (manager != NULL) {
//             answer.add(new JsonString(manager->getName()));
//         }
//     }
//     handler->writeToClient("userlist", &answer);
// }
}

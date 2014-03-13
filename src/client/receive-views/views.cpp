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
        emit handler->getWindow()->loginFailure();
    }
}

// void signup(JsonValue * message, UserHandler * handler) {
//     JsonDict * dictMessage = JDICT(message);

//     if (dictMessage == NULL) {
//         throw BadRequest("Malformatted request. Need a JSON dict");
//     }

//     string username = getString(dictMessage, "username");
//     string password = getString(dictMessage, "password");
//     string name = getString(dictMessage, "name");

//     string filename = handler->path("users", username);

//     if (fileExists(filename)) {
//         return sendFail(handler, 402, "login", "User already exists");
//     }

//     Manager * manager = new Manager(name, username, password);
//     handler->setManager(manager);

//     JsonDict answer;

//     answer.add("success", new JsonBool(true));
//     handler->writeToClient("login", &answer);
// }


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

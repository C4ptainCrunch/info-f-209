#include "user.h"

using namespace std;

namespace views {

void login(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    string username = getString(dictMessage, "username");
    string password = getString(dictMessage, "password");

    if (isInConnectedList(handler->getHandlers_list(), username)) {
        return sendFail(handler, 403, "login", "Already logged");
    }

    string filename = handler->path("users", username);
    string content;

    if (readFile(filename, content) != 0) {
        return sendFail(handler, 301, "login", "User does not exist");
    }

    Manager * manager = NULL;
    try {
        manager = new Manager(JsonValue::fromString(content));
    }
    catch (const ParseError & pe) {
        return sendFail(handler, 501, "login", "Error while retrieving user");
    }
    if (manager->checkPassword(password)) {
        JsonDict answer;

        answer.add("success", new JsonBool(true));
        handler->writeToClient("login", &answer);
        handler->setManager(manager);
    }
    else {
        delete manager;
        manager = NULL;
        return sendFail(handler, 401, "login", "Wrong password");
    }
}

void signup(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    string username = getString(dictMessage, "username");
    string password = getString(dictMessage, "password");
    string name = getString(dictMessage, "name");

    if (isInConnectedList(handler->getHandlers_list(), username)) {
        return sendFail(handler, 403, "login", "Already logged");
    }
    string filename = handler->path("users", username);

    if (fileExists(filename)) {
        return sendFail(handler, 402, "login", "User already exists");
    }

    Manager * manager = new Manager(name, username, password);
    handler->setManager(manager);

    JsonDict answer;

    answer.add("success", new JsonBool(true));
    handler->writeToClient("login", &answer);
}


void userlist(JsonValue * message, UserHandler * handler) {
    JsonList answer;
    std::vector<UserHandler *> * handlers_vector = handler->getHandlers_list();

    for (int i = 0; i < handlers_vector->size(); i++) {
        Manager * manager = handlers_vector->at(i)->getManager();
        if ((manager != NULL) && (manager != handler->getManager())) {
            answer.add(new JsonString(manager->getName()));
        }
    }
    handler->writeToClient("userlist", &answer);
}
}

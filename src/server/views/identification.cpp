#include "identification.h"

using namespace std;

void login(JsonValue * message, UserHandler * handler){
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL){
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    string username = getString(dictMessage, "username");
    string password = getString(dictMessage, "password");

    string filename = "data/users/"+username+".json";
    string content;

    if (readFile(filename, content) != 0){
       return sendFail(handler, 301, "login", "User does not exist");
    }

    Manager * manager = new Manager(JsonValue::fromString(content));
    if (manager->checkPassword(password)){
        JsonDict answer;

        JsonBool b = JsonBool(true);
        answer.add("success", &b);
        handler->writeToClient("login", &answer);
        handler->setManager(manager);
    }
    else {
        delete manager;
        manager = NULL;
        return sendFail(handler, 401, "login", "Wrong password");
    }
}

void signup(JsonValue * message, UserHandler * handler){
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL){
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    string username = getString(dictMessage, "username");
    string password = getString(dictMessage, "password");
    string name = getString(dictMessage, "name");


    // // TODO : add defence against path injection
    // string filename = "data/users/"+username+".json";
    // // TODO : check if user arleady exists
    // string content;

    Manager * manager = new Manager(name, username, password);
    handler->setManager(manager);

    JsonDict answer;

    JsonBool b = JsonBool(true);
    answer.add("success", &b);
    handler->writeToClient("login", &answer);
}

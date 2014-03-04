#include "identification.h"

using namespace std;

void logIn(JsonValue * message, UserHandler * handler){
    JsonDict * dictMessage = JDICT(message);
    JsonDict answer;

    if (dictMessage != NULL){
        // TODO : Check if cast is not null
        string userName = *JSTRING((*dictMessage)["username"]);
        string password = *JSTRING((*dictMessage)["password"]);

        string rawFileName = "data/users/"+userName+".json";
        string content;

        const char * fileName = rawFileName.c_str();
        if (readFile(fileName, content) == 0){
            Manager * user = new Manager(JsonValue::fromString(content));
            if (user->checkPassword(password)){
                JsonBool b = JsonBool(true);
                answer.add("success", &b);
                handler->writeToClient("login", &answer);
                handler->setManager(user);
            }
            else {
                delete user;
                user = NULL;
            }
            delete user;
        }
        else {
            JsonBool b = JsonBool(false);
            answer.add("success", &b);
            handler->writeToClient("login", &answer);
        }
    }
    else {
        JsonBool b = JsonBool(false);
        answer.add("success", &b);
        handler->writeToClient("login", &answer);
    }
}

// void signUp(JsonValue * message, UserHandler * handler){
//     JsonDict * dictMessage = JDICT(message);
//     JsonInt * code = new JsonInt();
//     code->setValue(FAIL);
//     if (dictMessage != NULL){
//         string userName = (*dictMessage)[USERNAME]->toString();
//         string rawFileName = "data/users/"+userName+".json";
//         string content;
//         const char * fileName = rawFileName.c_str();
//         if(readFile(fileName, content) == -1 and errno == EIO){
//             Manager * user = new Manager((*dictMessage)[NAME]->toString(), userName, (*dictMessage)[PASSWORD]->toString());
//             handler->setManager(user);
//             JsonDict * userInfos = JsonDict::fromString("{\"essai\" : \"lol\"}");//user->toJson();
//             string infos = userInfos->toString();
//             if (writeFile(fileName, infos) == 0){
//                 code->setValue(SUCCESS);
//             }
//         }
//     }
//     handler->writeToClient(code->toString());
//     delete code;
// }

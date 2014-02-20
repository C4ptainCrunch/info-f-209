#include "identification.h"

void logIn(JsonValue * message, UserHandler * thread){
    JsonDict * dictMessage = JDICT(message);
    JsonInt * code = new JsonInt();
    code->setValue(FAIL);
    if (dictMessage != NULL){
        std::string userName = (*dictMessage)[USERNAME]->toString();
        std::string password = (*dictMessage)[PASSWORD]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if (readFile(fileName, content) == 0){
            JsonDict * userInfos = JDICT(JsonValue::fromString(content));
            if (userInfos != NULL){
                Manager * user = new Manager(userInfos);
                if ((*userInfos)[PASSWORD]->toString() == password){
                    code->setValue(SUCCESS);
                    thread->setManager(user);
                }
                else {
                    delete user;
                }
                delete userInfos;
            }
        }
    }
    thread->writeToClient(code->toString());
    delete code;
}

void signUp(JsonValue * message, UserHandler * thread){
    JsonDict * dictMessage = JDICT(message);
    JsonInt * code = new JsonInt();
    code->setValue(FAIL);
    if (dictMessage != NULL){
        std::string userName = (*dictMessage)[USERNAME]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if(readFile(fileName, content) == -1 and errno == EIO){
            Manager * user = new Manager((*dictMessage)[NAME]->toString(), userName, (*dictMessage)[PASSWORD]->toString());
            thread->setManager(user);
            JsonDict * userInfos = JsonDict::fromString("{\"essai\" : \"lol\"}");//user->toJson();
            std::string infos = userInfos->toString();
            if (writeFile(fileName, infos) == 0){
                code->setValue(SUCCESS);
            }
        }
    }
    thread->writeToClient(code->toString());
    delete code;
}

int main(){
    return 0;
}
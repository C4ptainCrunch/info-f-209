#include "../models/Manager.h"
#include "../lib/json/utils.h"
#include <cstdlib>
#include <vector>
#include "../lib/file/files.cpp"
#include "../lib/json/json.h"
#include "../server/UserHandler.h"
#include "constants.h"

void logIn(JsonValue * message, UserHandler * thread){
    JsonDict * dictMessage = JDICT(message);
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
                    thread->setManager(user);
                    thread->writeToClient((JsonInt(CODE_SUCCESS)).toString());
                }
                else {
                    thread->writeToClient((JsonInt(CODE_BAD_PASSWORD)).toString());
                    delete user;
                }
                delete userInfos;
            }
            else{
                thread->writeToClient((JsonInt(CODE_BAD_PASSWORD_FORMAT)).toString());
            }
        }
        else {
            thread->writeToClient((JsonInt(CODE_ACCOUNT_NOT_FOUND)).toString());
        }
    }
    else{
        thread->writeToClient((JsonInt(CODE_WRONG_MESSAGE_FORMAT)).toString());
    }
    delete dictMessage;
}

void signUp(JsonValue * message, UserHandler * thread){
    JsonDict * dictMessage = JDICT(message);
    if (dictMessage != NULL){
        std::string userName = (*dictMessage)[USERNAME]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if(readFile(fileName, content) == -1 and errno == EIO){
            Manager * user = new Manager((*dictMessage)[NAME]->toString(), userName, (*dictMessage)[PASSWORD]->toString());
            thread->setManager(user);
            JsonDict * userInfos = user->toJson();
            std::string infos = userInfos->toString();
            if (writeFile(fileName, infos) == 0){
                thread->writeToClient((JsonInt(CODE_SUCCESS)).toString());
            }
            else{
                thread->writeToClient((JsonInt(CODE_FAIL_TO_SAVE)).toString());
            }
        }
        else{
            thread->writeToClient((JsonInt(CODE_ACCOUNT_ALREADY_EXIST)).toString());
        }
    }
    else{
        thread->writeToClient((JsonInt(CODE_WRONG_MESSAGE_FORMAT)).toString());
    }
    delete dictMessage;
}

int main(int argc, char * argv[]){
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
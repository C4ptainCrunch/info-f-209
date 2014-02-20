#include "../models/Manager.h"
#include "../lib/json/utils.h"
#include <cstdlib>
#include <vector>
#include "../lib/file/files.cpp"
#include "../lib/json/json.h"
#include "../server/UserHandler.h"

void logIn(JsonValue * message, UserHandler * thread)  // message = "user:password", TO DO : message en json
{
    JsonDict * dict = JDICT(message);
    if (dict != NULL){
        std::string userName = (*dict)["username"]->toString();
        std::string password = (*dict)["password"]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if (readFile(fileName, content) == 0){
            JsonDict * userInfos = JDICT(JsonValue::fromString(content));
            if (userInfos != NULL){
                if ((*userInfos)["hash"]->toString() == password){
                    thread->writeToClient("user.login : {signal : \"loginSuccess\"}");
                    thread->setManager(new Manager(userInfos));
                }
                else {
                    thread->writeToClient("user.login : {signal : \"wrongPassword\"}");
                }
                delete userInfos;
            }
            else{
                thread->writeToClient("user.login : {signal : \"wrongPasswordFormat\"}");
            }
        }
        else {
            thread->writeToClient("user.login : {signal : \"accountNotFound\"}");
        }
    }
    else{
        thread->writeToClient("user.login : {signal : \"wrongMessageFormat\"}");
    }
    delete dict;
}

void signUp(JsonValue * message, UserHandler * thread)
{
    JsonDict * dict = JDICT(message);
    if (dict != NULL){
        std::string userName = (*dict)["username"]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if(readFile(fileName, content) == -1 and errno == EIO){
            Manager * user = new Manager((*dict)["name"]->toString(), userName, (*dict)["password"]->toString());
            thread->setManager(user);
            JsonDict * userInfos = user->toJson();
            std::string infos = userInfos->toString();
            if (writeFile(fileName, infos) == 0){
                thread->writeToClient("user.signup : {signal = \"signupSuccess\"}");
            }
            else{
                thread->writeToClient("user.signup : {signal = \"failToSave\"}");
            }
        }
        else{
            thread->writeToClient("user.signup : {signal = \"accountAlreadyExist\"}");
        }
    }
    else{
        thread->writeToClient("user.login : {signal : \"wrongMessageFormat\"}");
    }
    delete dict;
}

int main(int argc, char * argv[]){
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
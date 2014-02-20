#include "../models/Manager.h"
#include "../lib/json/utils.h"
#include <cstdlib>
#include <vector>
#include "../lib/file/files.cpp"
#include "../lib/json/json.h"
#include "../server/UserHandler.h"

void logIn(JsonValue * message, UserHandler * thread)  // message = "user:password", TO DO : message en json
{
    JsonDict * dictMessage = JDICT(message);
    if (dictMessage != NULL){
        std::string userName = (*dictMessage)["username"]->toString();
        std::string password = (*dictMessage)["password"]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if (readFile(fileName, content) == 0){
            JsonDict * userInfos = JDICT(JsonValue::fromString(content));
            if (userInfos != NULL){
                Manager * user = new Manager(userInfos);
                if ((*userInfos)["password"]->toString() == password){
                    thread->setManager(user);
                    thread->writeToClient("user.login : {signal : \"loginSuccess\"}");
                }
                else {
                    thread->writeToClient("user.login : {signal : \"wrongPassword\"}");
                    delete user;
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
    delete dictMessage;
}

void signUp(JsonValue * message, UserHandler * thread)
{
    JsonDict * dictMessage = JDICT(message);
    if (dictMessage != NULL){
        std::string userName = (*dictMessage)["username"]->toString();
        std::string rawFileName = "data/users/"+userName+".json";
        std::string content;
        const char * fileName = rawFileName.c_str();
        if(readFile(fileName, content) == -1 and errno == EIO){
            Manager * user = new Manager((*dictMessage)["username"]->toString(), userName, (*dictMessage)["password"]->toString());
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
    delete dictMessage;
}

int main(int argc, char * argv[]){
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
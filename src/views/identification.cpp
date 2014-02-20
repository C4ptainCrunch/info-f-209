//#include "json.h"  module json à coder
#include "thread.h"
#include "Manager.h"
#include <cstlib>
#include <vecteur>
#include "json.h"
#include "utils.h"

void logIn(JsonDict * message, UserHandler * thread)  // message = "user:password", TO DO : message en json
{
    std::String userName = message["username"];
    std::String password = message["password"];
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if(readFile(filename, &content) == 0){
        JsonDict * userInfos =  dynamic_cast<JsonDict*> JsonValue::fromString(content);
        if(userInfos["hash"] == password){
            thread->writeToClient("user.login : {signal : \"loginSuccess\"}");
            thread->setUser(new Manager(userInfos));
        }
        else{
            thread->writeToClient("user.login : {signal : \"wrongPassword\"}");
        }
        delete userInfos;
    }
    else{
        thread->writeToClient("user.login : {signal : \"accountNotFound\"}");
    }
}

void signUp(JsonDict * message, UserHandler * thread)
{
    std::string userName = message["username"]
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if(readFile(filename, &content) == -1 and errno=EIO){
        Manager * user = new Manager(message["name"], userName, message["password"], new Club());
        thread->setUser(user);
        std::string infos = (user->toJson())->toString();
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

int main(int argc, char * argv[]){
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
//#include "json.h"  module json à coder
#include "thread.h"
#include "Manager.h"
#include <cstlib>
#include "json.h"
#include "utils.h"

void logIn(std::String message, UserHandler * thread)  // message = "user:password", TO DO : message en json
{
    std::String reponse;
    int index = message.find(":");
    std::String userName = message.substr(0, index+1);
    std::String password = message.substr(index, message.lenght());
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if(readFile(filename, &content) == 0){
        JsonDict * userInfos =  dynamic_cast<JsonDict*> JsonValue::toString(content);
        // TO DO : changer la ligne en dessous en qqch de propre
        Manager * user = new Manager(userInfos["name_"], userName, userInfos["hash_"], new Club(userInfos["club_"][money_], userInfos["club_"][team_]));
        if(user->checkPassword(password)){
            thread.writeToClient("user.login : {signal = \"loginSuccess\"}");
            thread.setUser(user);
        }
        else{
            thread.writeToClient("user.login : {signal = \"wrongPassword\"}");
            delete(user);
        }
    }
    else{
        thread.writeToClient("user.login : {signal = \"accountNotFound\"}");
    }
}

void signUp(char * message, Thread * thread)
{
    std::String reponse;
    int index = message.find(":");
    std::String userName = message.substr(0, index+1);
    std::String password = message.substr(index, message.lenght());
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if(readFile(filename, &content) == -1 and errno=EIO){
        //JsonValue json(content);
        //TO DO : récupérer info de json
        Club * club = new Club();
        Manager * user = new Manager("Kong", userName, "Banane", club);
        thread.writeToClient("user.signup : {signal = \"signupSuccess\"}");
        thread.setUser(user);
        thread.addUserDatas(userName, json.get("password"));  // rajoute le nouveau compte
        }
    }
    else{
        thread.writeToClient("user.signup : {signal = \"accountAlreadyExist\"}");
    }
}

int main(int argc, char * argv[]){
    if(argc <= 1){
        std::cout<<"Invalid parameters"<<std::endl;
        exit(0);
    }
    std::string lol;
    char * file = argv[1];
    int state = readFile(file, lol);
    if (state == -1){
        std::cout<<"Erreur en lecture "<<std::endl;
        exit(1);
    }
    std::cout<<lol<<std::endl;
    state = writeFile("lol.txt", lol);
    if (state == -1){
        std::cout<<"Erreur en écriture "<<std::endl;
        exit(1);
    }
    std::cout<<"Success"<<std::endl;
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
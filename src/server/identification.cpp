//#include "json.h"  module json à coder
#include "thread.h"
#include "Manager.h"

void logIn(std::String message, UserHandler * thread)  // message = "user:password", TO DO : message en json
{
    std::String reponse;
    int index = message.find(":");
    std::String userName = message.substr(0, index+1);
    std::String password = message.substr(index, message.lenght());
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if (1){ // test TO DO : delete la ligne
    //if(readFile(filename, &content) == 0){
        //JsonObject json(content);
        //TO DO : récupérer info de json
        Club * machin = new Club();
        Manager * user = new Manager("Kong", userName, "Banane", machin);
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

void signUp(char* message, Thread * thread)
{
    std::String reponse;
    int index = message.find(":");
    std::String userName = message.substr(0, index+1);
    std::String password = message.substr(index, message.lenght());
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if (1){ // test TO DO : delete la ligne
    //if(readFile(filename, &content) == -1 and errno=EIO){
        //JsonObject json(content);
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
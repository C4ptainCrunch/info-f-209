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
            thread.writeToClient("user.login : {signal : \"loginSuccess\"}");
            thread.setUser(new Manager(userInfos));
        }
        else{
            thread.writeToClient("user.login : {signal : \"wrongPassword\"}");
        }
        delete(userInfos);
    }
    else{
        thread.writeToClient("user.login : {signal : \"accountNotFound\"}");
    }
}

void signUp(JsonDict * message, UserHandler * thread)
{
    std::string userName = message["username"]
    char * filename = "data/users/"+userName+".json";
    std::String content;
    if(readFile(filename, &content) == -1 and errno=EIO){
        Manager * user = new Manager(message["name"], userName, message["password"], new Club());
        thread.setUser(user);
        std::string infos = convertInfos(user);
        if (writeFile(fileName, infos) == 0){
            thread.writeToClient("user.signup : {signal = \"signupSuccess\"}");
        }
        else{
            thread.writeToClient("user.signup : {signal = \"failToSave\"}");
        }
    }
    else{
        thread.writeToClient("user.signup : {signal = \"accountAlreadyExist\"}");
    }
}

/*std::string convertInfos(Manager * user){
    std::string infos = "{name : " + user->getName() + ", username : ";
    infos =+ user->getUserName() "}";
    int index = 0;
    while (index > user->get){
        JsonDict * player = infos["club_"]["players_"][index]; //TO DO : Optimiser la taille des lignes
        players.push_back(new NonFieldPlayer(player["vocation"], player["speed"], player["force"], player["agility"], player["reflexes"], player["passPrecision"], player["wounded"], /*TO dO : inventaire*/NULL, player["level"], player["experience"])); //TO DO : object ou pointeur NoNFieldPlayer
/*        index++;
    }
    for (int i = 0 ; i < (int) infos["club_"]["team"].size() ; i++){
        JsonDict * player = infos["club_"]["team"][i];
        team[i]= new NonFieldPlayer(player["vocation"], player["speed"], player["force"], player["agility"], player["reflexes"], player["passPrecision"], player["wounded"], /*TO dO : inventaire*/NULL, player["level"], player["experience"])));
/*    }
    for (int j = 0 ; j < (int) infos["club_"]["installations"].size() ; j++){
        installations[i] = new Installation(infos["club_"]["installations"][j]["level"]);
    }
    Manager * user = new Manager(infos["name"], infos["username"], infos["hash_"], new Club(infos["club_"]["money_"], new Team(team), players);
    return (std::string) infos;
}*/



int main(int argc, char * argv[]){
    /*if(argc <= 1){
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
    std::cout<<"Success"<<std::endl;*/
    return EXIT_SUCCESS;    // TO DO : vérifier si EXIT_SUCCESS à return
}
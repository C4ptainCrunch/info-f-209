#include "Manager.h"
using namespace std;

Manager::Manager(string name, string userName, string password, Club club): name_(name), userName_(userName), club_(club){
    free = true;
    //TODO : Hash du password
}

Manager::Manager(JsonValue * json){
    JsonDict * manager = JDICT(json);
    if(manager == NULL){
        throw 1;
    }

    Club club = Club((*manager)["club"]);

    JsonString * name_string = JSTRING((*manager)["name"]);
    if(name_string == NULL)
        throw 1;
    string name = * name_string;

    JsonString * username_string = JSTRING((*manager)["username"]);
    if(username_string == NULL)
        throw 1;
    string username = * username_string;

    JsonString * password_string = JSTRING((*manager)["password"]);
    if(password_string == NULL)
        throw 1;
    string password = * password_string;

    Manager(name, username, password, club);
}

Manager::~Manager(){}

bool Manager::checkPassword(const string password){
    //TODO
    return true;
}

void Manager::changePassword(const string password){
    //TODO
}

Club* Manager::getClub(){
    return &club_;
}

string Manager::getUserName(){
    return userName_;
}

string Manager::getName(){
    return name_;
}

bool Manager::isFree(){
    return free;
}

void Manager::setFreeState(bool state){
    free = state;
}


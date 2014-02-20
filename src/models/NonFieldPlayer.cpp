#include "NonFieldPlayer.h"
#include <iostream>

using namespace std;

NonFieldPlayer::NonFieldPlayer(int vocation, int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory, int level, int experience) : level_(level), experience_(experience), vocation_(vocation) {
    Player(speed, force, agility, reflexes, passPrecision, wounded, inventory);
}

NonFieldPlayer::NonFieldPlayer(): level_(1), experience_(0), vocation_(0) {
    Player();
}

NonFieldPlayer::NonFieldPlayer(JsonValue * json){
    JsonDict * player_dict = JDICT(json);

    if(player_dict == NULL)
        throw 1;

    JsonInt * vocation_int = JINT((*player_dict)["vocation"]);
    if(vocation_int == NULL)
        throw 1;
    int vocation = * vocation_int;

    JsonInt * speed_int = JINT((*player_dict)["speed"]);
    if(speed_int == NULL)
        throw 1;
    int speed = * speed_int;

    JsonInt * force_int = JINT((*player_dict)["force"]);
    if(force_int == NULL)
        throw 1;
    int force = * force_int;

    JsonInt * agility_int = JINT((*player_dict)["agility"]);
    if(agility_int == NULL)
        throw 1;
    int agility = * agility_int;

    JsonInt * reflexes_int = JINT((*player_dict)["reflexes"]);
    if(reflexes_int == NULL)
        throw 1;
    int reflexes = * reflexes_int;

    JsonInt * passPrecision_int = JINT((*player_dict)["passPrecision"]);
    if(passPrecision_int == NULL)
        throw 1;
    int passPrecision = * passPrecision_int;

    JsonInt * level_int = JINT((*player_dict)["level"]);
    if(level_int == NULL)
        throw 1;
    int level = * level_int;

    JsonInt * experience_int = JINT((*player_dict)["experience"]);
    if(experience_int == NULL)
        throw 1;
    int experience = * experience_int;

    JsonBool * wounded_bool = JBOOL((*player_dict)["wounded"]);
    if(wounded_bool == NULL)
        throw 1;
    bool wounded = * wounded_bool;

    JsonList * item_list = JLIST((*player_dict)["inventory"]);
    if(item_list == NULL)
        throw 1;

    std::vector<Item> inventory;
    for(int i = 0; i < item_list->size(); i++){
        inventory.push_back(Item((*item_list)[i]));
    }

    NonFieldPlayer(vocation, speed, force, agility, reflexes, passPrecision,  wounded, inventory, level, experience);
}

NonFieldPlayer::~NonFieldPlayer(){}

NonFieldPlayer & NonFieldPlayer::operator=(const Player & player){
    if (this != &player){
        speed_ = player.getSpeed();
        force_ = player.getForce();
        agility_ = player.getAgility();
        reflexes_ = player.getReflexes();
        passPrecision_ = player.getPassPrecision();
        wounded_ = player.isWounded();
        inventory_ = player.getInventory();
    }
    return *this;
}

int NonFieldPlayer::getLevel(){
    return level_;
}

void NonFieldPlayer::changeExperience(int deltaExperience){
    experience_ += deltaExperience;
}

void NonFieldPlayer::levelUp(){
    level_ += 1;
}

int NonFieldPlayer::getVocation(){
    return vocation_;
}

void NonFieldPlayer::setVocation(int vocation){
    vocation_ = vocation;
}

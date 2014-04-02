#include "FieldPlayer.h"

using namespace std;

FieldPlayer::FieldPlayer(int role, bool guest): role_(role), guest_(guest) {}

FieldPlayer::FieldPlayer(): role_(0) {
    guest_ = false;

}

FieldPlayer::~FieldPlayer() {}

FieldPlayer::FieldPlayer(NonFieldPlayer & nonFieldPlayer, int role, bool guest) {
    speed_ = nonFieldPlayer.getSpeed();
    force_ = nonFieldPlayer.getForce();
    agility_ = nonFieldPlayer.getAgility();
    reflexes_ = nonFieldPlayer.getReflexes();
    passPrecision_ = nonFieldPlayer.getPassPrecision();
    wounded_ = nonFieldPlayer.isWounded();
    inventory_ = nonFieldPlayer.getInventory();
    role_ = role;
    guest_ = guest;

}

FieldPlayer::FieldPlayer(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory, int role, bool guest): Player(speed, force, agility, reflexes, passPrecision, wounded, inventory), role_(role), guest_(guest){}

FieldPlayer::FieldPlayer(JsonValue * json) {
    JsonDict * player_dict = JDICT(json);

    if (player_dict == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    JsonInt * speed_int = JINT((*player_dict)["speed"]);
    if (speed_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int speed = *speed_int;

    JsonInt * force_int = JINT((*player_dict)["force"]);
    if (force_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int force = *force_int;

    JsonInt * agility_int = JINT((*player_dict)["agility"]);
    if (agility_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int agility = *agility_int;

    JsonInt * reflexes_int = JINT((*player_dict)["reflexes"]);
    if (reflexes_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int reflexes = *reflexes_int;

    JsonInt * passPrecision_int = JINT((*player_dict)["passPrecision"]);
    if (passPrecision_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int passPrecision = *passPrecision_int;

    JsonBool * wounded_bool = JBOOL((*player_dict)["wounded"]);
    if (wounded_bool == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    bool wounded = *wounded_bool;

    JsonList * item_list = JLIST((*player_dict)["inventory"]);
    if (item_list == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    std::vector<Item> inventory;
    for (int i = 0; i < item_list->size(); i++) {
        inventory.push_back(Item((*item_list)[i]));
    }

    JsonInt * role_int = JINT((*player_dict)["role"]);
    if (role_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int role = *role_int;

    JsonBool * guest_bool = JBOOL((*player_dict)["guest"]);
    if (guest_bool == NULL){
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    bool guest = *guest_bool;

    new(this) FieldPlayer(speed, force, agility, reflexes, passPrecision, wounded, inventory, role, guest);
}

FieldPlayer & FieldPlayer::operator=(Player & player) {
    if (this != &player) {
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
bool FieldPlayer::isInGuestTeam() {
    return guest_;
}

void FieldPlayer::move() {}

void FieldPlayer::hitBudger() {}

void FieldPlayer::catchGoldenSnitch() {}

void FieldPlayer::throwQuaffle() {}

void FieldPlayer::catchQuaffle() {}

void FieldPlayer::testMove() {}


void FieldPlayer::setRole(int role) {
    role_ = role;
}

int FieldPlayer::getRole() {
    return role_;
}

FieldPlayer::operator JsonDict() const {
    JsonDict r;
    r.add("speed", new JsonInt(speed_));
    r.add("force", new JsonInt(force_));
    r.add("agility", new JsonInt(agility_));
    r.add("reflexes", new JsonInt(reflexes_));
    r.add("passPrecision", new JsonInt(passPrecision_));
    r.add("wounded", new JsonBool(wounded_));

    r.add("role", new JsonInt(role_));
    r.add("guest", new JsonBool(guest_));

    JsonList * inventory = new JsonList();
    for (int i = 0; i < inventory_.size(); i++) {
        JsonDict * item = new JsonDict(inventory_[i]);
        inventory->add(item);
    }
    r.add("inventory", inventory);

    return r;
}

#include "Manager.h"
using namespace std;

Manager::Manager(string name, string userName, string password, Club club): name_(name), userName_(userName), club_(club), hash_(password) {
    ready = true;
}

Manager::Manager(JsonValue * json) {
    JsonDict * manager = JDICT(json);
    if (manager == NULL) {
        throw ModelUnserializationError("Manager : hasn't got a dict");
    }
    Club club;
    JsonDict * club_json = JDICT((*manager)["club"]);
    if (club_json == NULL) {
        club = Club();
    }
    else {
        club = Club(club_json);
    }

    JsonString * name_string = JSTRING((*manager)["name"]);
    if (name_string == NULL) {
        throw ModelUnserializationError("Manager : missing name");
    }
    string name = *name_string;

    JsonString * username_string = JSTRING((*manager)["username"]);
    if (username_string == NULL) {
        throw ModelUnserializationError("Manager : missing username");
    }
    string username = *username_string;

    JsonString * password_string = JSTRING((*manager)["hash"]);
    if (password_string == NULL) {
        throw ModelUnserializationError("Manager : missing hash");
    }
    string password = *password_string;

    new (this) Manager(name, username, password, club);
}

Manager::~Manager() {}

bool Manager::checkPassword(const string password) {
    return password == hash_;
}

void Manager::changePassword(const string password) {
    hash_ = password;
}

Club * Manager::getClub() {
    return &club_;
}

string Manager::getUserName() {
    return userName_;
}

string Manager::getName() {
    return name_;
}

bool Manager::isReady() {
    return ready;
}

void Manager::setReadyState(bool state) {
    ready = state;
}

Manager::operator JsonDict() const {
    JsonDict r;

    r.add("name", new JsonString(name_));
    r.add("username", new JsonString(userName_));
    r.add("hash", new JsonString(hash_));
    JsonValue * club = new JsonValue(club_);
    r.add("club", club);

    return r;
}

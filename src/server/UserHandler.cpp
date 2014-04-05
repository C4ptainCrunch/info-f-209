#include "UserHandler.h"

using namespace std;


#include "views/user.h"
#include "views/management.h"
#include "views/challenge.h"
#include "views/match.h"

const map<string, view_ptr> UserHandler::viewmap = {
    {"login", views::login},
    {"register", views::signup},
    {"userlist", views::userlist},
    {"playerlist", views::playerlist},
    {"challenge", views::challenge},
    {"accept_challenge", views::accept_challenge},
    {"refuse_challenge", views::refuse_challenge},
    {"end_turn", views::end_turn},
    {"surrender", views::surrender}
};

UserHandler::UserHandler(struct server_shared_data * shared_data, Socket * socket) {
    shared_data_ = shared_data;
    s_ = socket;
    manager_ = NULL;
}

UserHandler::~UserHandler() {
    delete s_;
    for (int i = 0; i < shared_data_->handlers_list.size(); i++) {
        if (shared_data_->handlers_list.at(i) == this) {
            shared_data_->handlers_list.erase(shared_data_->handlers_list.begin() + i);
            break;
        }
    }
    if (manager_ != NULL) {
        writeToFile();
        delete manager_;
    }
}


std::vector<UserHandler *> * UserHandler::getHandlers_list() {
    return &(shared_data_->handlers_list);
}

std::vector<Match *> * UserHandler::getMatch_list() {
    return &(shared_data_->match_list);
}

vector<Challenge> * UserHandler::getChalenge_list() {
    return &(shared_data_->challenge_list);
}

struct server_shared_data * UserHandler::getSharedData() {
    return shared_data_;
}

Manager * UserHandler::getManager() {
    return manager_;
}

UserHandler * UserHandler::findHandler(string username) {
    for (int i = 0; i < shared_data_->handlers_list.size(); i++) {
        if (shared_data_->handlers_list.at(i)->getManager()->getUserName() == username) {
            return shared_data_->handlers_list.at(i);
        }
    }
    return NULL;
}

UserHandler * UserHandler::findHandler(Manager * manager) {
    for (int i = 0; i < shared_data_->handlers_list.size(); i++) {
        if (shared_data_->handlers_list.at(i)->getManager() == manager) {
            return shared_data_->handlers_list.at(i);
        }
    }
    return NULL;
}

void UserHandler::setManager(Manager * manager) {
    if (manager_ == NULL) {
        manager_ = manager;
    }
}

int UserHandler::writeToClient(std::string key, JsonValue * json) {
    return s_->write(key + ":" + json->toString());
}

void UserHandler::disconnect() {
    dead = true;
}

int UserHandler::loop() {
    string message;
    while (1) {
        if ((s_->read(message) <= 0) || (message == "quit")) {
            disconnect();
            return 0;
        }
        handleMessage(message);
    }
}

void UserHandler::handleMessage(string message) {
    string key;

    message = split_message(&key, message);
    try {
        try {
            UserHandler::viewmap.at (key)(JsonValue::fromString(message), this);
        }
        catch (const std::out_of_range & oor) {
            throw BadRequest("Unknown topic : '" + key + "'");
        }
    }
    catch (const BadRequest & br) {
        JsonDict answer;

        answer.add("Bad request", new JsonString(br.what()));
        answer.add("code", new JsonInt(100));
        this->writeToClient("error", &answer);
    }
    catch (const ParseError & pe) {
        JsonDict answer;

        answer.add("Parse error", new JsonInt(101));
        answer.add("code", new JsonString(pe.what()));
        this->writeToClient("error", &answer);
    }
}

Match * UserHandler::getMatch() {
    for (int i = 0; i < shared_data_->match_list.size(); i++) {
        Match * m = shared_data_->match_list.at(i);
        if ((m->getClubs()[0] == manager_->getClub()) || (m->getClubs()[1] == manager_->getClub())) {
            return m;
        }
    }

    return NULL;
}

bool UserHandler::inMatch() {
    return getMatch() != NULL;
}

string UserHandler::path(string dir, string var) {
    // TODO : add defence against path injection
    return shared_data_->datapath + dir + "/" + var + ".json";
}


bool UserHandler::writeToFile() {
    string content = ((JsonDict)(*manager_)).toString();
    string fileName = path("users", manager_->getUserName());

    if (writeFile(fileName, content)) {
        perror("Save user ");
        return false;
    }
    else {
        return true;
    }
}

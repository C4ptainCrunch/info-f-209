#include "UserHandler.h"

using namespace std;


#include "views/user.h"
#include "views/management.h"

const map<string, view_ptr> UserHandler::viewmap = {
    {"login", views::login},
    {"register", views::signup},
    {"userlist", views::userlist},
    {"playerlist", views::playerlist}
};

UserHandler::UserHandler(std::vector<UserHandler *> * handlers_list, std::vector<Match *> * match_list, string datapath) {
    pthread_mutex_init(&ready_lock, NULL);
    handlers_list_ = handlers_list;
    match_list_ = match_list;
    datapath_ = datapath;
    s_ = NULL;
    manager_ = NULL;
}

void UserHandler::start(Socket * fd, thread * handling_thread) {
    pthread_mutex_lock(&ready_lock);
    handling_thread_ = handling_thread;
    s_ = fd;
    pthread_mutex_unlock(&ready_lock);
}

UserHandler::~UserHandler() {
    delete s_;
    for (int i = 0; i < handlers_list_->size(); i++) {
        if (handlers_list_->at(i) == this) {
            handlers_list_->erase(handlers_list_->begin() + i);
            break;
        }
    }
    if (manager_ != NULL) {
        writeToFile();
        delete manager_;
    }
}

bool UserHandler::isReady() {
    pthread_mutex_lock(&ready_lock);
    bool ready = s_ != NULL;
    pthread_mutex_unlock(&ready_lock);
    return ready;
}

std::vector<UserHandler *> * UserHandler::getHandlers_listPtr() {
    return handlers_list_;
}

std::vector<Match *> * UserHandler::getMatch_listPtr(){
    return match_list_;
}

Manager * UserHandler::getManager() {
    return manager_;
}

UserHandler * UserHandler::findHandler(string username) {
    for(int i = 0; i < handlers_list_->size(); i++){
        if(handlers_list_->at(i)->getManager()->getUserName() == username){
            return handlers_list_->at(i);
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

Match * UserHandler::getMatch(){
    for(int i = 0; i < match_list_->size(); i++){
        Match * m = match_list_->at(i);
        if(m->getClubs()[0] == manager_->getClub() || m->getClubs()[1] == manager_->getClub()){
            return m;
        }
    }

    return NULL;
}

bool UserHandler::inMatch(){
    return getMatch() != NULL;
}

string UserHandler::path(string dir, string var) {
    // TODO : add defence against path injection
    return datapath_ + dir + "/" + var + ".json";
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

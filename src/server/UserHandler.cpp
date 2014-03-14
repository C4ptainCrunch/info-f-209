#include "UserHandler.h"

using namespace std;


#include "views/user.h"

const map<string, view_ptr> UserHandler::viewmap = {
    {"login", views::login},
    {"register", views::signup},
    {"userlist", views::userlist}
};

UserHandler::UserHandler(std::vector<UserHandler *> * handlers_list, string datapath) {
    handlers_list_ = handlers_list;
    datapath_ = datapath;
    s_ = NULL;
    manager_ = NULL;
}

void UserHandler::start(const int fd, thread * handling_thread) {
    pthread_mutex_lock(&ready_lock);
    handling_thread_ = handling_thread;
    s_ = new Socket(fd);
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

Manager * UserHandler::getManager() {
    return manager_;
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
    s_->write("diconnect:true");
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

string UserHandler::path(string dir, string var) {
    // TODO : add defence against path injection
    return datapath_ + dir + "/" + var + ".json";
}

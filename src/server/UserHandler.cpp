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
    handling_thread_ = handling_thread;
    s_ = new Socket(fd);
}

UserHandler::~UserHandler() {
    delete s_;
    if (manager_ != NULL) {
        delete manager_;
    }
}

bool UserHandler::isReady() {
    return s_ != NULL;
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

        JsonString s = JsonString(br.what());
        JsonInt i = JsonInt(100);
        answer.add("Bad request", &s);
        answer.add("code", &i);
        this->writeToClient("error", &answer);
    }
    catch (const ParseError & pe) {
        JsonDict answer;

        JsonString s = JsonString(pe.what());
        JsonInt i = JsonInt(101);
        answer.add("Parse error", &s);
        answer.add("code", &i);
        this->writeToClient("error", &answer);
    }
}

string UserHandler::path(string dir, string var) {
    // TODO : add defence against path injection
    return datapath_ + dir + "/" + var + ".json";
}

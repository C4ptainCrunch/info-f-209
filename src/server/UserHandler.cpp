#include "UserHandler.h"

using namespace std;

const map<string,view_ptr> UserHandler::viewmap = {
    {"plop", plop},
    {"login", logIn}
};


UserHandler::UserHandler(std::vector<UserHandler *> * handlers_list) {
    handlers_list_ = handlers_list;
    s_ = NULL;
    manager_ = NULL;
}

void UserHandler::start(const int fd, thread * handling_thread){
    handling_thread_ = handling_thread;
    s_ = new Socket(fd);
}

UserHandler::~UserHandler() {
    delete s_;
    if(manager_ != NULL)
        delete manager_;
}

bool UserHandler::isReady(){
    return s_ != NULL;
}

std::vector<UserHandler *> * UserHandler::getHandlers_listPtr(){
    return handlers_list_;
}

Manager * UserHandler::getManager(){
    return manager_;
}

void UserHandler::setManager(Manager * manager){
    if(manager_ == NULL)
        manager_ = manager;
}

int UserHandler::writeToClient(std::string key, JsonValue * json){
    return s_->write(key + ":" + json->toString());
}

void UserHandler::disconnect(){
    dead = true;
    s_->write("diconnect:true");
}

int UserHandler::loop() {
    string message;
    while(1){
        if((s_->read(message) <= 0) || (message == "quit")){
            disconnect();
            return 0;
        }
        handleMessage(message);
    }
}

void UserHandler::handleMessage(string message){
    string key;

    message = split_message(&key, message);
    UserHandler::viewmap.at(key)(JsonValue::fromString(message), this);
}
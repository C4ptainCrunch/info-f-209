#include <vector>
#include <thread>
#include <string>

using namespace std;


#include "UserHandler.h"
#include "views.h"
#include "helpers.h"


UserHandler::UserHandler(std::vector<UserHandler *> * handlers_list) {
    handlers_list_ = handlers_list;
    s_ = NULL;
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

int UserHandler::writeToClient(string message){
    return s_->write(message);
}

void UserHandler::disconnect(){
    dead = true;
    s_->write("diconnect:true");
}

int UserHandler::loop() {
    string message;
    string key;
    while(1){
        if((s_->read(message) <= 0) || (message == "quit")){
            disconnect();
            return 0;
        }
        message = split_message(&key, message);
        plop(key, this);
    }
}

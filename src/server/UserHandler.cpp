#include <vector>
#include <thread>
#include <string>

using namespace std;


#include "UserHandler.h"


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

void UserHandler::loop() {
    std::string response = "";

    s_->write("Hello, ULB!");
    s_->read(response);
    s_->write(response);
    s_->read(response);
    s_->write(response);
    s_->write("Bye :)");
}

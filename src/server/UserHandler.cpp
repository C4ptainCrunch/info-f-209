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
}

bool UserHandler::isReady(){
    return s_ != NULL;
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

#ifndef HANDLE_H
#define HANDLE_H

#include "Socket.h"

class Manager {
    public:
        Manager();
        ~Manager();
};

using namespace std;

class UserHandler {
    public:
        UserHandler(std::vector<UserHandler*> * handlers_list);
        ~UserHandler();
        void start(const int fd, thread * handling_thread);
        bool isReady();
        void loop();

    private:
        Socket * s_;
        Manager * manager_;
        thread * handling_thread_;
        std::vector<UserHandler *> * handlers_list_;
};

//HANDLE_H
#endif

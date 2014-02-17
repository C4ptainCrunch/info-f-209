#ifndef HANDLE_H
#define HANDLE_H

#include "../lib/socket/Socket.h"
#include <vector>
#include <thread>

class Manager {};


class UserHandler {
    public:
        UserHandler(std::vector<UserHandler*> * handlers_list);
        ~UserHandler();
        void start(const int fd, thread * handling_thread);
        bool isReady();
        int loop();

        std::vector<UserHandler *> * getHandlers_listPtr();
        Manager * getManager();
        void setManager(Manager * manager);
        int writeToClient(string message);
        void disconnect();

    private:
        bool dead;
        Socket * s_;
        Manager * manager_;
        thread * handling_thread_;
        std::vector<UserHandler *> * handlers_list_;

        void handleMessage(std::string message);
};

//HANDLE_H
#endif
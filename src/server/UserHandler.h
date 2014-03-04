#ifndef HANDLE_H
#define HANDLE_H

#include <vector>
#include <thread>
#include <string>
#include <map>
#include <iostream>

#include "../common/lib/socket/Socket.h"
#include "../common/models/Manager.h"
#include "helpers.h"
#include "views/views.h"

class UserHandler;

typedef void (*view_ptr)(JsonValue *, UserHandler * );


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
        int writeToClient(std::string key, JsonValue * json);
        void disconnect();

    private:
        bool dead;
        Socket * s_;
        Manager * manager_;
        thread * handling_thread_;
        std::vector<UserHandler *> * handlers_list_;

        void handleMessage(std::string message);

        static const map<string,view_ptr> viewmap;
};
//HANDLE_H
#endif
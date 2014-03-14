#ifndef HANDLE_H
#define HANDLE_H

#include <vector>
#include <thread>
#include <string>
#include <map>
#include <iostream>
#include <pthread.h>

#include "../common/lib/socket/Socket.h"
#include "../common/models/Manager.h"
#include "../common/lib/exception/BadRequest.h"
#include "helpers.h"

class UserHandler;

typedef void (* view_ptr)(JsonValue *, UserHandler *);


class UserHandler {
public:
    UserHandler(std::vector<UserHandler *> * handlers_list, std::string datapath);
    ~UserHandler();
    void start(Socket * fd, std::thread * handling_thread);
    bool isReady();
    int loop();

    std::vector<UserHandler *> * getHandlers_listPtr();
    Manager * getManager();
    void setManager(Manager * manager);
    int writeToClient(std::string key, JsonValue * json);
    void disconnect();
    std::string path(std::string dir, std::string var);
    bool writeToFile();

private:
    bool dead;
    Socket * s_;
    Manager * manager_;
    std::thread * handling_thread_;
    std::vector<UserHandler *> * handlers_list_;
    std::string datapath_;
    pthread_mutex_t ready_lock;

    void handleMessage(std::string message);

    static const std::map<std::string, view_ptr> viewmap;
};
//HANDLE_H
#endif

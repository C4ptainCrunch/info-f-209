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
#include "../common/models/Match.h"
#include "../common/lib/exception/BadRequest.h"
#include "helpers.h"
#include "sharedData.h"

class UserHandler;

typedef void (* view_ptr)(JsonValue *, UserHandler *);


class UserHandler {
public:
    UserHandler(struct server_shared_data * shared_data);
    ~UserHandler();
    void start(Socket * fd, std::thread * handling_thread);
    bool isReady();
    int loop();

    std::vector<UserHandler *> * getHandlers_list();
    std::vector<Match *> * getMatch_list();
    std::vector<Challenge> * getChalenge_list();
    struct server_shared_data * getSharedData();
    Manager * getManager();
    UserHandler * findHandler(std::string);
    UserHandler * findHandler(Manager *);
    void setManager(Manager * manager);
    int writeToClient(std::string key, JsonValue * json);
    void disconnect();
    std::string path(std::string dir, std::string var);
    bool writeToFile();
    Match * getMatch();
    bool inMatch();

private:
    bool dead;
    Socket * s_;
    Manager * manager_;
    std::thread * handling_thread_;
    struct server_shared_data * shared_data_;
    pthread_mutex_t ready_lock;

    void handleMessage(std::string message);

    static const std::map<std::string, view_ptr> viewmap;
};
//HANDLE_H
#endif

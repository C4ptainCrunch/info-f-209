#ifndef SERVER_HANDLE_STRUCT_H
#define SERVER_HANDLE_STRUCT_H

#include <vector>
#include <string>

#include "../common/models/Manager.h"
#include "../common/models/Match.h"

class UserHandler;

struct Challenge {
    int id;
    Manager * opponents[2];
};

struct server_shared_data {
    std::vector<UserHandler *> handlers_list;
    std::vector<Match *> match_list;
    std::string datapath;
    std::vector<struct Challenge> challenge_list;
    int last_challenge_id;
};

#endif
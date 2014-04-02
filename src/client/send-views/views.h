#ifndef SVIEWS_H
#define SVIEWS_H

#include <vector>

#include "../../common/lib/json/json.h"
#include "../../common/lib/socket/Socket.h"

namespace sviews {
void login(Socket * s, std::string username, std::string password);
void signup(Socket * s, std::string username, std::string name, std::string password);
void userlist(Socket * s);
void playerlist(Socket * s);
void challenge(Socket * s, std::string username);
void refuseChallenge(Socket * s, std::string opponent);
void acceptChallenge(Socket * s, std::string opponent);
}


#endif // SVIEWS_H

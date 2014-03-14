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
}


#endif // SVIEWS_H

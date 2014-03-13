#ifndef RVIEWS_H
#define RVIEWS_H

#include <cstdlib>
#include <vector>

#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"

class ServerHandler;

namespace rviews {
void login(JsonValue * message, ServerHandler * handler);
void signup(JsonValue * message, ServerHandler * handler);
void userlist(JsonValue * message, ServerHandler * handler);
}

#include "serverhandler.h"

#endif // RVIEWS_H

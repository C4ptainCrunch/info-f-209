#ifndef RVIEWS_H
#define RVIEWS_H

#include <cstdlib>
#include <vector>

#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"
#include "../../common/models/NonFieldPlayer.h"

class ServerHandler;

namespace rviews {
void login(JsonValue * message, ServerHandler * handler);
void signup(JsonValue * message, ServerHandler * handler);
void userlist(JsonValue * message, ServerHandler * handler);
void playerlist(JsonValue * message, ServerHandler * handler);
void startMatch(JsonValue * message, ServerHandler * handler);
void challenge(JsonValue* message, ServerHandler * handler);
}

#include "serverhandler.h"

#endif // RVIEWS_H

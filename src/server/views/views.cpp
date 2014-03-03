#include "views.h"

void plop(JsonValue * message, UserHandler * handler){
    handler->writeToClient("pong", message);
}
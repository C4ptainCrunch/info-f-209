#include "views.h"
#include <iostream>
using namespace std;

void plop(JsonValue * message, UserHandler * handler){
    handler->writeToClient("pong", message);
}
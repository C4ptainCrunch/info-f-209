#include "views.h"


void plop(std::string message, UserHandler * handler){
    handler->writeToClient(message);
}
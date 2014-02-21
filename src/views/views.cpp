#include "views.h"
#include <iostream>
using namespace std;

void plop(JsonValue * message, UserHandler * handler){
    cout << "enter plop" << endl;
    cout << message->toString() << endl;
    handler->writeToClient("pong", message);
}
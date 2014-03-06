#include "helpers.h"

using namespace std;

void sendFail(UserHandler * handler, int errorcode, string topic, string message){
    JsonDict answer;

    JsonBool b = JsonBool(false);
    JsonString s = JsonString(message);
    answer.add("success", &b);
    answer.add("reason", &s);
    handler->writeToClient(topic, &answer);
}
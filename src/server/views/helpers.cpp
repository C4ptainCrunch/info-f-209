#include "helpers.h"

using namespace std;

void sendFail(UserHandler * handler, int errorcode, string topic, string message){
    JsonDict answer;

    JsonBool b = JsonBool(false);
    JsonString s = JsonString(message);
    JsonInt i = JsonInt(errorcode);
    answer.add("success", &b);
    answer.add("reason", &s);
    answer.add("code", &i);
    handler->writeToClient(topic, &answer);
}
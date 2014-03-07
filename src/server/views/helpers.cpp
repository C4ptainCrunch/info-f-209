#include "helpers.h"

using namespace std;

void sendFail(UserHandler * handler, int errorcode, string topic, string message) {
    JsonDict answer;

    answer.add("success", new JsonBool(false));
    answer.add("reason", new JsonString(message));
    answer.add("code", new JsonInt(errorcode));
    handler->writeToClient(topic, &answer);
}

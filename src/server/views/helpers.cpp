#include "helpers.h"

using namespace std;

void sendFail(UserHandler * handler, int errorcode, string topic, string message) {
    JsonDict answer;

    answer.add("success", new JsonBool(false));
    answer.add("reason", new JsonString(message));
    answer.add("code", new JsonInt(errorcode));
    handler->writeToClient(topic, &answer);
}

bool isInConnectedList(std::vector<UserHandler *> * listUserHandler, string userName) {
    bool ret = false;
    for (int i = 0; i < listUserHandler->size() && !ret; i++) {
        if (listUserHandler->at(i)->getManager() != NULL) {
            ret = listUserHandler->at(i)->getManager()->getUserName() == userName;
        }
    }
    return ret;
}

#include "server.h"

using namespace std;


void thread_loop(UserHandler * handler) {
    while (!handler->isReady()) {
        usleep(10000);
    }
    try {
        handler->loop();
    }
    catch (...) {
        try {
            JsonDict answer;

            answer.add("Error", new JsonString("Unknown error"));
            answer.add("code", new JsonInt(500));
            handler->writeToClient("error", &answer);
        }
        catch (...) {}
        cout << "Uncought exception, this is bad !" << endl;
    }
    delete handler;
    cout << "Client disconnected." << endl;
}

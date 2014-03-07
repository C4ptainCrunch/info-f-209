#include "server.h"

using namespace std;


void thread_loop(UserHandler * handler) {
    while (!handler->isReady()) {
        usleep(10000);
    }
    try {
        handler->loop();
    }
    catch(...){
        try {
            JsonDict answer;

            JsonString s = JsonString("Unknown error");
            JsonInt i = JsonInt(500);
            answer.add("Error", &s);
            answer.add("code", &i);
            handler->writeToClient("error", &answer);
        }
        catch(...){}
        cout << "Uncought exception, this is bad !" << endl;
    }
    delete handler;
    cout << "Client disconnected." << endl;
}

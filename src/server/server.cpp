#include "server.h"

using namespace std;


void thread_loop(UserHandler * handler){
    while(!handler->isReady()){
        usleep(10000);
    }

    handler->loop();
    delete handler;
    cout << "Client disconnected." << endl;
}
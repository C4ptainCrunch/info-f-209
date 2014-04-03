#include "thread.h"

using namespace std;

Thread::Thread(void * (* routine) (void *), void * p) {
    pthread_create(&tid, NULL, routine, p);
}

bool Thread::alive(){
    return pthread_kill(tid, 0) == 0;
}

void * Thread::join() {
    void * result;
    pthread_join(tid, &result);
    return result;
}

#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <pthread.h>
#include <signal.h>

#include <unistd.h>

class Thread {
public:
    Thread(void * (* routine) (void *), void * p=NULL);
    void * join();
    bool alive();

private:
    pthread_t tid;
};

#endif

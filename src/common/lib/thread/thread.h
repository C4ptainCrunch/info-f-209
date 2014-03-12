#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <pthread.h>

#include <unistd.h>

#define SECOND 1000000

class Thread {
public:
    Thread(void *(*routine) (void *), void * p = NULL);
    void* join();

private:
    pthread_t tid;
};

#endif

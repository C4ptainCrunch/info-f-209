#ifndef THREAD_H
#define THREAD_H

#include <stdlib.h>
#include <unistd.h>
#include "helpers.h"

#define RCV_SIZE 2
#include "Socket.h"

void connection(const int socket);

#endif //THREAD_H

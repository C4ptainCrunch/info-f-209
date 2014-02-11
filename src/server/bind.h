#ifndef BIND_H
#define BIND_H

#define BACKLOG 10
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include <string>

#include "helpers.h"

int bindTo(char* port);


#endif // BIND_H

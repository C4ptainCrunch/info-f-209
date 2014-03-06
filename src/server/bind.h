#ifndef BIND_H
#define BIND_H

#define BACKLOG 10
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#include <string>

#include "helpers.h"

int bindTo(int port_i);


#endif // BIND_H

#ifndef CLIENT_LOOP
#define CLIENT_LOOP

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <iostream>

#include "helpers.h"
#include "UserHandler.h"

int main(int argc, char * argv[]);

void * client_loop(void *);

#endif

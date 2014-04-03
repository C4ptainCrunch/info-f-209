#ifndef SERVER_H
#define SERVER_H

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

#endif // SERVER_H

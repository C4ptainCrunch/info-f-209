#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <thread>
#include <vector>
#include <iostream>

#include "helpers.h"
#include "bind.h"
#include "UserHandler.h"

int main(int argc, char *argv[]);

void thread_loop(UserHandler * handler);

#endif // SERVER_H

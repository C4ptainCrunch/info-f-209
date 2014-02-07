#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <thread>
#include <vector>

#include "helpers.cpp"
#include "thread.cpp"
#include "bind.cpp"

int main(int argc, char *argv[]);

#endif // SERVER_H

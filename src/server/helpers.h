#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>

#include <string>

#define RCV_SIZE 2

std::string recieveFrom(const int sock, char * buffer);

std::string split_message(std::string * key, std::string message);

#endif // HELPERS_H
